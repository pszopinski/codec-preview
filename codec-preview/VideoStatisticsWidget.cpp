#include "VideoStatisticsWidget.h"
#include "ui_VideoStatisticsWidget.h"

VideoStatisticsWidget::VideoStatisticsWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoStatisticsWidget) {
    ui->setupUi(this);

    // redirect stream probe output to file (cannot read it in any other way
    // unfortunately)
    streamProbeProcess.setStandardOutputFile(PROBE_FILE_NAME);

    // react to frame probe output with parseFrameProbeOutput
    connect(&frameProbeProcess, &QProcess::readyRead, this,
            &VideoStatisticsWidget::parseFrameProbeOutput);

    // react to stream probe output with parseStreamProbeOutput
    connect(&streamProbeProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(parseStreamProbeOutput(int, QProcess::ExitStatus)));

    ui->lBitrate->setToolTip(paramManager.getHint("Bitrate"));

}

VideoStatisticsWidget::~VideoStatisticsWidget() { delete ui; }

void VideoStatisticsWidget::stopProbe() {
    frameProbeProcess.kill();
    streamProbeProcess.kill();
    frameProbeProcess.waitForFinished();
    streamProbeProcess.waitForFinished();
}

void VideoStatisticsWidget::parseFrameProbeOutput() {

    // read output line by line
    while (frameProbeProcess.canReadLine()) {
        QString output = frameProbeProcess.readLine();

        // find frame type
        if (output.startsWith("pict_type=")) {
            // put single character describing frame type into queue
            framesQueue.enqueue(output.toUtf8().constData()[10]);

            // throw out oldest frame types if over queue size limit
            if (framesQueue.size() > 16)
                stopProbe();
            // framesQueue.dequeue();

            // create snapshot of queue to display in widget
            QString framesQueueSnapshot;

            QListIterator<char> i(framesQueue);

            while (i.hasNext()) {
                framesQueueSnapshot.append(i.next());
            }

            ui->frameTypes->setText(framesQueueSnapshot);
        }

        // find frame width
        if (output.startsWith("width=")) {
            ui->frameWidth->setText(output.mid(6, output.length()));
        }

        // find frame height
        if (output.startsWith("height=")) {
            ui->frameHeight->setText(output.mid(7, output.length()));
        }
    }
}

void VideoStatisticsWidget::clearFrameQueue() {
    framesQueue.clear();
    ui->frameTypes->setText("");
}

void VideoStatisticsWidget::startFrameProbe(QString command) {
    frameProbeProcess.start(command);
}

void VideoStatisticsWidget::startStreamProbe(QString command) {
    streamProbeProcess.start(command);
}

void VideoStatisticsWidget::setFrameTypeText(QString text)
{
    ui->frameTypes->setText(text);
}

void VideoStatisticsWidget::parseStreamProbeOutput(int a, QProcess::ExitStatus b) {
    // to silence unused warning
    (void)a;
    (void)b;

    // read from data dumped into file
    std::ifstream myReadFile;
    myReadFile.open(PROBE_FILE_NAME.toUtf8().data());
    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {

            myReadFile >> output;

            QString fileOutput = QString(output);

            // find frame rate
            if (fileOutput.startsWith("avg_frame_rate=")) {
                ui->frameRate->setText(fileOutput.mid(15, fileOutput.length()));
            }

        }
    } else {
        qDebug() << "ERROR: cannot access file";
    }
    myReadFile.close();
}

void VideoStatisticsWidget::onStatsChange(VlcStats *stats){
    ui->decodedBlocks->setText(QString::number(stats->decoded_video));
    ui->bitRate->setText(QString::number(stats->input_bitrate*10000));
    ui->framesDropped->setText(QString::number(stats->lost_pictures));
    ui->bytesRead->setText(QString::number(stats->read_bytes/100.0));
    ui->framesCount->setText(QString::number(stats->displayed_pictures));
    }
