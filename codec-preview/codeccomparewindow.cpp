#include "codeccomparewindow.h"
#include "ui_codeccomparewindow.h"

CodecCompareWindow::CodecCompareWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::CodecCompareWindow) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    vlcInstance = new VlcInstance({""}, NULL);

    for (int i = 0; i < 4; i++) {
        // initialize media objects
        vlcMedia[i] =
            new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + compareWindowHosts[i] +
                             ":" + compareWindowPorts[i],
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
    /*connect(&frameProbes[0], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput0);

    connect(&frameProbes[3], &QProcess::readyRead, this,
            &CodecCompareWindow::parseFrameProbeOutput3);*/

    connect(this, &CodecCompareWindow::statsChanged1, ui->videoInfo1,
            &VideoInfoWidget::onStatsChange);
    connect(this, &CodecCompareWindow::statsChanged2, ui->videoInfo2,
            &VideoInfoWidget::onStatsChange);
    connect(this, &CodecCompareWindow::statsChanged3, ui->videoInfo3,
            &VideoInfoWidget::onStatsChange);

    connect(vlcMediaPlayers[1], &VlcMediaPlayer::timeChanged, this,
            &CodecCompareWindow::whilePlaying1);
    connect(vlcMediaPlayers[2], &VlcMediaPlayer::timeChanged, this,
            &CodecCompareWindow::whilePlaying2);
    connect(vlcMediaPlayers[3], &VlcMediaPlayer::timeChanged, this,
            &CodecCompareWindow::whilePlaying3);
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

    ui->videoInfo1->stopProbe();
    ui->videoInfo2->stopProbe();
    ui->videoInfo3->stopProbe();
}

CodecManager *CodecCompareWindow::getManager(int i) {

    switch (i) {
    case 0:
        return mjpegManager;
        break;
    case 1:
        return h261Manager;
        break;
    case 2:
        return mpeg1Manager;
        break;
    case 3:
        return mpeg2Manager;
        break;
    case 4:
        return h264Manager;
        break;
    case 5:
        return h265Manager;
        break;
    }
    return NULL;
}

void CodecCompareWindow::setManagers(int one, int two, int three) {
    ui->encodedParams1->setVisible(false);
    ui->encodedParams2->setVisible(false);
    ui->encodedParams3->setVisible(false);

    switch (one) {
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

    switch (two) {
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

    switch (three) {
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

    /*for (int i = 0; i < 4; i++) {
        QString frameProbeCommand =
    FfmpegCommand::getFrameProbeCommand(compareWindowHosts[i],
    compareWindowPorts[i]); frameProbes[i].start(frameProbeCommand); QString
    streamProbeCommand =
    FfmpegCommand::getStreamProbeCommand(compareWindowHosts[i],
    compareWindowPorts[i]); streamProbes[i].start(streamProbeCommand);
    }*/
    QString frameProbeCommand = FfmpegCommand::getFrameProbeCommand(
        compareWindowHosts[1], compareWindowPorts[1]);
    ui->videoInfo1->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = FfmpegCommand::getStreamProbeCommand(
        compareWindowHosts[1], compareWindowPorts[1]);
    ui->videoInfo1->startStreamProbe(streamProbeCommand);
    frameProbeCommand = FfmpegCommand::getFrameProbeCommand(
        compareWindowHosts[2], compareWindowPorts[2]);
    ui->videoInfo2->startFrameProbe(frameProbeCommand);
    streamProbeCommand = FfmpegCommand::getStreamProbeCommand(
        compareWindowHosts[2], compareWindowPorts[2]);
    ui->videoInfo2->startStreamProbe(streamProbeCommand);
    frameProbeCommand = FfmpegCommand::getFrameProbeCommand(
        compareWindowHosts[3], compareWindowPorts[3]);
    ui->videoInfo3->startFrameProbe(frameProbeCommand);
    streamProbeCommand = FfmpegCommand::getStreamProbeCommand(
        compareWindowHosts[3], compareWindowPorts[3]);
    ui->videoInfo3->startStreamProbe(streamProbeCommand);
}

void CodecCompareWindow::whilePlaying1() {
    emit statsChanged1(vlcMedia[1]->getStats());
}

void CodecCompareWindow::whilePlaying2() {
    emit statsChanged2(vlcMedia[2]->getStats());
}

void CodecCompareWindow::whilePlaying3() {
    emit statsChanged3(vlcMedia[3]->getStats());
}
