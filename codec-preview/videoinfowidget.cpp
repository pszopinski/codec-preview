#include "videoinfowidget.h"
#include "ui_videoinfowidget.h"

VideoInfoWidget::VideoInfoWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoInfoWidget) {
    ui->setupUi(this);
    streamProbeProcess.setStandardOutputFile(PROBE_FILE_NAME);

    ui->frameTypes->setReadOnly(true);
    ui->frameWidth->setReadOnly(true);
    ui->frameHeight->setReadOnly(true);
    ui->codecName->setReadOnly(true);
    ui->bitRate->setReadOnly(true);
    ui->aspectRatio->setReadOnly(true);

    connect(&frameProbeProcess, &QProcess::readyRead, this,
            &VideoInfoWidget::parseFrameProbeOutput);

    connect(&streamProbeProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(parseStreamProbeOutput(int, QProcess::ExitStatus)));
}

VideoInfoWidget::~VideoInfoWidget() { delete ui; }

void VideoInfoWidget::stopProbe() {
    frameProbeProcess.kill();
    streamProbeProcess.kill();
    frameProbeProcess.waitForFinished();
    streamProbeProcess.waitForFinished();
}

void VideoInfoWidget::parseFrameProbeOutput() {
    while (frameProbeProcess.canReadLine()) {
        QString output = frameProbeProcess.readLine();

        if (output.startsWith("pict_type=")) {
            framesQueue.enqueue(output.toUtf8().constData()[10]);
            if (framesQueue.size() > 16)
                framesQueue.dequeue();

            QString framesQueueSnapshot;

            QListIterator<char> i(framesQueue);

            while (i.hasNext()) {
                framesQueueSnapshot.append(i.next());
            }

            ui->frameTypes->setText(framesQueueSnapshot);
        }

        if (output.startsWith("width=")) {
            ui->frameWidth->setText(output.mid(6, output.length()));
        }
        if (output.startsWith("height=")) {
            ui->frameHeight->setText(output.mid(7, output.length()));
        }
    }
}

void VideoInfoWidget::clearFrameQueue() {
    framesQueue.clear();
    ui->frameTypes->setText("");
}

void VideoInfoWidget::startFrameProbe(QString command) {
    frameProbeProcess.start(command);
}

void VideoInfoWidget::startStreamProbe(QString command) {
    streamProbeProcess.start(command);
}

void VideoInfoWidget::parseStreamProbeOutput(int a, QProcess::ExitStatus b) {
    (void)a;
    (void)b;

    // qDebug() << "start reading";
    std::ifstream myReadFile;
    myReadFile.open(PROBE_FILE_NAME.toUtf8().data());
    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {

            myReadFile >> output;
            // qDebug() << output;

            QString fileOutput = QString(output);

            if (fileOutput.startsWith("avg_frame_rate=")) {
                // qDebug() << "got some output for frame rate";
                ui->frameRate->setText(fileOutput.mid(15, fileOutput.length()));
            }

            if (fileOutput.startsWith("codec_name=")) {
                ui->codecName->setText(fileOutput.mid(11, fileOutput.length()));
            }

            if (fileOutput.startsWith("bit_rate=")) {
                ui->bitRate->setText(fileOutput.mid(9, fileOutput.length()));
            }

            if (fileOutput.startsWith("display_aspect_ratio=")) {
                ui->aspectRatio->setText(
                    fileOutput.mid(21, fileOutput.length()));
            }
        }
    } else {
        qDebug() << "cannot access file";
    }
    myReadFile.close();
    qDebug() << "stop reading";
}
