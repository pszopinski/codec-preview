#ifndef SHOWCODECS_H
#define SHOWCODECS_H

#include "constants.h"
#include <QDebug>
#include <QProcess>
#include <QString>
#include <QWidget>
#include <VLCQtCore/Audio.h>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtCore/Stats.h>

namespace Ui {
class ShowCodecs;
}

class ShowCodecs : public QWidget {
    Q_OBJECT

  public:
    explicit ShowCodecs(QWidget *parent = 0);
    ~ShowCodecs();
    void initVideos();
    void initVlc();
    void setInputLocation(QString location);
    void setCodecInd(int first, int second);
    void broadcast(QString streamingCommand1, QString streamingCommand2);

  private:
    Ui::ShowCodecs *ui;
    VlcMedia *vlcMediaEncoded1;
    VlcMediaPlayer *vlcPlayerEncoded1;
    VlcMedia *vlcMediaEncoded2;
    VlcMediaPlayer *vlcPlayerEncoded2;
    VlcInstance *vlcInstance;
    QString inputLocation;
    int firstCodecIndex;
    int secondCodecIndex;
    QProcess streamingProcess1;
    QProcess streamingProcess2;
};

#endif // SHOWCODECS_H
