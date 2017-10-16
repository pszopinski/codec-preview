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

void CodecCompareWindow::stream(QString streamingCommand) {
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();
    }

    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();

    // start streaming process
    streamingProcess.start(streamingCommand);


    for (int i = 0; i < 4; i++) {
        vlcMediaPlayers[i]->play();
    }

    /*for (int i = 0; i < 4; i++) {
        QString frameProbeCommand = ui->codecTabs->getFrameProbeCommand("a", "b");
        ui->videoInfo->startFrameProbe(frameProbeCommand);
        QString streamProbeCommand = ui->codecTabs->getStreamProbeCommand();
        ui->videoInfo->startStreamProbe(streamProbeCommand);
    }*/
}
