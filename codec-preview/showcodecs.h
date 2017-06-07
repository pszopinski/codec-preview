#ifndef SHOWCODECS_H
#define SHOWCODECS_H

#include <QWidget>
#include <QString>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/MediaPlayer.h>
#include "codeccomparisonwindow.h"
#include "constants.h"

namespace Ui {
class ShowCodecs;
}

class ShowCodecs : public QWidget
{
    Q_OBJECT

public:
    explicit ShowCodecs(QWidget *parent = 0);
    ~ShowCodecs();

    VlcMediaPlayer* getVlcPlayerEncoded1();
    VlcMediaPlayer* getVlcPlayerEncoded2();
    void initVideos();
    void setMainWindowHandler(CodecComparisonWindow* ccw);
    void initVlc();
    void setInputLocation(QString location);
    void setCodecInd(int first, int second);
    void broadcast();


private:
    Ui::ShowCodecs *ui;
    VlcMedia *vlcMediaEncoded1;
    VlcMediaPlayer *vlcPlayerEncoded1;
    VlcMedia *vlcMediaEncoded2;
    VlcMediaPlayer *vlcPlayerEncoded2;
    CodecComparisonWindow* ccw;
    VlcInstance *vlcInstance;
    QString inputLocation;
    int firstCodecIndex;
    int secondCodecIndex;
    QProcess streamingProcess1;
    QProcess streamingProcess2;

};

#endif // SHOWCODECS_H
