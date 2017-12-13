#ifndef VIDEOPLAYBACKWIDGET_H
#define VIDEOPLAYBACKWIDGET_H

#include <QDebug>
#include <QWidget>

#include <VLCQtCore/Audio.h>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Stats.h>

#include "constants.h"

namespace Ui {
class VideoPlaybackWidget;
}

class VideoPlaybackWidget : public QWidget {
    Q_OBJECT
  private:
    Ui::VideoPlaybackWidget *ui;
    VlcInstance *vlcInstance;
    VlcMedia *vlcMediaRaw;
    VlcMediaPlayer *vlcPlayerRaw;
    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;
    VlcStats *stats;

  public:
    explicit VideoPlaybackWidget(QWidget *parent = 0);
    ~VideoPlaybackWidget();
    void stopPlayers();
    void startPlayers();
    void originalSize(QSize frameSize);
    void restoreDefaultSize();

  private slots:
    void whilePlaying();

  signals:
    void statsChanged(VlcStats *stats);
};

#endif // VIDEOPLAYBACKWIDGET_H
