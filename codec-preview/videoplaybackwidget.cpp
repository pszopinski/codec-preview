#include "videoplaybackwidget.h"
#include "ui_videoplaybackwidget.h"

VideoPlaybackWidget::VideoPlaybackWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::VideoPlaybackWidget) {
    this->showMaximized();
    ui->setupUi(this);

    vlcInstance = new VlcInstance(VlcCommon::args(), NULL);

    // Initialize raw video display
    vlcPlayerRaw = new VlcMediaPlayer(vlcInstance);
    vlcPlayerRaw->setVideoWidget(ui->rawVideo);
    vlcPlayerRaw->audio()->setMute(true);
    ui->rawVideo->setMediaPlayer(vlcPlayerRaw);
    vlcMediaRaw = new VlcMedia(RAW_VIDEO_PROTOCOL + "://@" + RAW_VIDEO_HOST +
                                   ":" + RAW_VIDEO_PORT,
                               false, vlcInstance);
    vlcPlayerRaw->openOnly(vlcMediaRaw);

    // Initialize encoded video display
    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    vlcPlayerEncoded->audio()->setMute(true);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);
    vlcMediaEncoded =
        new VlcMedia(ENCODED_VIDEO_PROTOCOL + "://@" + ENCODED_VIDEO_HOST +
                         ":" + ENCODED_VIDEO_PORT,
                     false, vlcInstance);
    vlcPlayerEncoded->openOnly(vlcMediaEncoded);
}

VideoPlaybackWidget::~VideoPlaybackWidget() { delete ui; }

void VideoPlaybackWidget::stopPlayers() {
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();
}

void VideoPlaybackWidget::startPlayers() {
    qDebug() << "Starting the players...";
    vlcPlayerRaw->setTime(0);
    vlcPlayerEncoded->setTime(0);
    vlcPlayerRaw->play();
    vlcPlayerEncoded->play();
}
