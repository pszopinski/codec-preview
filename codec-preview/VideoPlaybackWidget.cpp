#include "VideoPlaybackWidget.h"
#include "ui_videoplaybackwidget.h"

VideoPlaybackWidget::VideoPlaybackWidget(QWidget *parent) : QWidget(parent), ui(new Ui::VideoPlaybackWidget) {
    ui->setupUi(this);

    vlcInstance = new VlcInstance({""}, NULL);

    QString rawAddress = RAW_VIDEO_PROTOCOL + "://@" + rawVideoHost + ":" + rawVideoPort;
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://@" + encodedVideoHost + ":" + encodedVideoPort;

    // initialize raw video display
    vlcPlayerRaw = new VlcMediaPlayer(vlcInstance);
    vlcPlayerRaw->setVideoWidget(ui->rawVideo);
    vlcPlayerRaw->audio()->setMute(true);
    ui->rawVideo->setMediaPlayer(vlcPlayerRaw);

    // initialize encoded video display
    vlcPlayerEncoded = new VlcMediaPlayer(vlcInstance);
    vlcPlayerEncoded->setVideoWidget(ui->encodedVideo);
    vlcPlayerEncoded->audio()->setMute(true);
    ui->encodedVideo->setMediaPlayer(vlcPlayerEncoded);

    connect(vlcPlayerEncoded, &VlcMediaPlayer::timeChanged, this, &VideoPlaybackWidget::whilePlaying);
}

VideoPlaybackWidget::~VideoPlaybackWidget() { delete ui; }

void VideoPlaybackWidget::stopPlayers() {
    vlcPlayerRaw->stop();
    vlcPlayerEncoded->stop();
}

void VideoPlaybackWidget::startPlayers() {
    QString rawAddress = RAW_VIDEO_PROTOCOL + "://@" + rawVideoHost + ":" + rawVideoPort;
    QString encodedAddress = ENCODED_VIDEO_PROTOCOL + "://@" + encodedVideoHost + ":" + encodedVideoPort;

    vlcMediaRaw = new VlcMedia(rawAddress, false, vlcInstance);

    vlcMediaEncoded = new VlcMedia(encodedAddress, false, vlcInstance);

    vlcPlayerRaw->setTime(0);
    vlcPlayerEncoded->setTime(0);

    vlcPlayerRaw->open(vlcMediaRaw);
    vlcPlayerEncoded->open(vlcMediaEncoded);
}

void VideoPlaybackWidget::whilePlaying() { emit statsChanged(vlcMediaEncoded->getStats()); }

void VideoPlaybackWidget::originalSize(QSize frameSize) {
    ui->rawVideo->setFixedSize(frameSize.width(), frameSize.height());
    ui->encodedVideo->setFixedSize(frameSize.width(), frameSize.height());
}

void VideoPlaybackWidget::restoreDefaultSize() {
    ui->rawVideo->setMinimumSize(0, 0);
    ui->encodedVideo->setMinimumSize(0, 0);
    ui->rawVideo->setMaximumSize(16777215, 16777215);
    ui->encodedVideo->setMaximumSize(16777215, 16777215);
}
