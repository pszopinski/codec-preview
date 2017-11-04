#include "codeccomparewindow.h"
#include "ui_codeccomparewindow.h"

CodecCompareWindow::CodecCompareWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecCompareWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);

    for (int i = 0; i < 4; i++) {
        // initialize media objects
        vlcMedia[i] = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" +
                                       compareWindowHosts[i] + ":" + compareWindowPorts[i],
                                   false, vlcInstance);

        // initialize video displays
        vlcMediaPlayers[i] = new VlcMediaPlayer(vlcInstance);
        vlcMediaPlayers[i]->audio()->setMute(true);
        vlcMediaPlayers[i]->openOnly(vlcMedia[i]);
    }

    // connect video widgets
    vlcMediaPlayers[0]->setVideoWidget(ui->rawVideo);
    ui->rawVideo->setMediaPlayer(vlcMediaPlayers[0]);
    vlcMediaPlayers[1]->setVideoWidget(ui->encodedVideo1);
    ui->encodedVideo1->setMediaPlayer(vlcMediaPlayers[1]);
    vlcMediaPlayers[2]->setVideoWidget(ui->encodedVideo2);
    ui->encodedVideo2->setMediaPlayer(vlcMediaPlayers[2]);
    vlcMediaPlayers[3]->setVideoWidget(ui->encodedVideo3);
    ui->encodedVideo3->setMediaPlayer(vlcMediaPlayers[3]);


    // init labels
    original = ui->original;
    label1 = ui->first;
    label2 = ui->second;
    label3 = ui->third;



    // react to frame probe output with parseFrameProbeOutput
    connect(&frameProbes[0], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput0);

    connect(&frameProbes[3], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput3);

}

CodecCompareWindow::~CodecCompareWindow() { delete ui; }

void CodecCompareWindow::closeEvent(QCloseEvent *event) {
    (void)event;
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();
    }
    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();
}

void CodecCompareWindow::setManagers(int one, int two, int three)
{
    ui->encodedParams1->setVisible(false);
    ui->encodedParams2->setVisible(false);
    ui->encodedParams3->setVisible(false);

    switch(one) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams1, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams1, h265Manager);
        break;
    }

    switch(two) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams2, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams2, h265Manager);
        break;
    }

    switch(three) {
    case 0:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mjpegManager);
        break;
    case 1:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h261Manager);
        break;
    case 2:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mpeg1Manager);
        break;
    case 3:
        ui->outerLayout->replaceWidget(ui->encodedParams3, mpeg2Manager);
        break;
    case 4:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h264Manager);
        break;
    case 5:
        ui->outerLayout->replaceWidget(ui->encodedParams3, h265Manager);
        break;
    }


}

void CodecCompareWindow::stream(QString streamingCommand) {
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();

        frameProbes[i].kill();
        frameProbes[i].waitForFinished();

        streamProbes[i].kill();
        streamProbes[i].waitForFinished();
    }

    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();

    // start streaming process
    streamingProcess.start(streamingCommand);


    for (int i = 0; i < 4; i++) {
        vlcMediaPlayers[i]->play();
    }

    for (int i = 0; i < 4; i++) {
        QString frameProbeCommand = FfmpegCommand::getFrameProbeCommand(compareWindowHosts[i], compareWindowPorts[i]);
        frameProbes[i].start(frameProbeCommand);
        QString streamProbeCommand = FfmpegCommand::getStreamProbeCommand(compareWindowHosts[i], compareWindowPorts[i]);
        streamProbes[i].start(streamProbeCommand);
    }
}

void CodecCompareWindow::parseFrameProbeOutput0() {
    // read output line by line
    while (frameProbes[0].canReadLine()) {
        QString output = frameProbes[0].readLine();

        // find frame type
        if (output.startsWith("pict_type=")) {
            // put single character describing frame type into queue
            framesQueues[0].enqueue(output.toUtf8().constData()[10]);

            // throw out oldest frame types if over queue size limit
            if (framesQueues[0].size() > 16) {
                frameProbes[0].kill();
                frameProbes[0].waitForFinished();
            }
            // framesQueue.dequeue();

            // create snapshot of queue to display in widget
            QString framesQueueSnapshot;

            QListIterator<char> i(framesQueues[0]);

            while (i.hasNext()) {
                framesQueueSnapshot.append(i.next());
            }

            ui->frames0->setText(framesQueueSnapshot);
        }
    }



}


void CodecCompareWindow::parseFrameProbeOutput3() {

    while (frameProbes[3].canReadLine()) {
        QString output = frameProbes[3].readLine();

        // find frame type
        if (output.startsWith("pict_type=")) {
            // put single character describing frame type into queue
            framesQueues[3].enqueue(output.toUtf8().constData()[10]);

            // throw out oldest frame types if over queue size limit
            if (framesQueues[3].size() > 16) {
                frameProbes[3].kill();
                frameProbes[3].waitForFinished();
            }
            // framesQueue.dequeue();

            // create snapshot of queue to display in widget
            QString framesQueueSnapshot;

            QListIterator<char> i(framesQueues[3]);

            while (i.hasNext()) {
                framesQueueSnapshot.append(i.next());
            }

            ui->frames3->setText(framesQueueSnapshot);
        }
    }
}
