#include "showcodecs.h"
#include "ui_showcodecs.h"

ShowCodecs::ShowCodecs(QWidget *parent)
    : QWidget(parent), ui(new Ui::ShowCodecs) {
    setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);

    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);

    for (int i = 0; i < 4; i++) {
        // initialize media objects
        vlcMedia[i] = new VlcMedia(VIDEO_PROTOCOLS[i] + "://@" +
                                       VIDEO_HOSTS[i] + ":" + VIDEO_PORTS[i],
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
}

ShowCodecs::~ShowCodecs() { delete ui; }

void ShowCodecs::closeEvent(QCloseEvent *event) {
    (void)event;
    for (int i = 0; i < 4; i++) {
        // stop player
        vlcMediaPlayers[i]->stop();
    }
    // kill streaming process
    streamingProcess.kill();
    streamingProcess.waitForFinished();
}

void ShowCodecs::broadcast(QString streamingCommand) {
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
}
