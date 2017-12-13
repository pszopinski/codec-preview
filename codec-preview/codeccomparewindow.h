#ifndef CODECCOMPAREWINDOW_H
#define CODECCOMPAREWINDOW_H

#include "constants.h"
#include <QDebug>
#include <QLabel>
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
#include <QQueue>

#include "codectabs/codecmanager.h"
#include "codectabs/mjpegmanager.h"
#include "codectabs/h261manager.h"
#include "codectabs/h264manager.h"
#include "codectabs/h265manager.h"
#include "codectabs/mpeg1manager.h"
#include "codectabs/mpeg2manager.h"



#include "ffmpegcommand.h"

namespace Ui {
class CodecCompareWindow;
}

class CodecCompareWindow : public QWidget {
    Q_OBJECT

  private:
    Ui::CodecCompareWindow *ui;
    VlcInstance *vlcInstance;
    VlcMedia *vlcMedia[4];
    VlcMediaPlayer *vlcMediaPlayers[4];
    QProcess streamingProcess;
    QProcess frameProbes[4];
    QProcess streamProbes[4];
    QQueue<char> framesQueues[4];

  public:
    explicit CodecCompareWindow(QWidget *parent = 0);
    ~CodecCompareWindow();
    void stream(QString streamingCommand);
    void closeEvent(QCloseEvent *event);
    void setManagers(int one, int two, int three);
    CodecManager* getManager(int i);

    QLabel *original;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

    CodecManager* h261Manager = new CodecManager("h261","h261","matroska",this);
    CodecManager* h264Manager = new CodecManager("h264","libx264","matroska",this);
    CodecManager* h265Manager = new CodecManager("h265","libx265","matroska",this);
    CodecManager* mjpegManager = new CodecManager("mjpeg","mjpeg","matroska",this);
    CodecManager* mpeg1Manager = new CodecManager("mpeg1","mpeg1video","mpegts",this);
    CodecManager* mpeg2Manager = new CodecManager("mpeg2","mpeg2video","mpegts",this);

private slots:
    void whilePlaying1();
    void whilePlaying2();
    void whilePlaying3();

signals:
    void statsChanged1(VlcStats *stats);
    void statsChanged2(VlcStats *stats);
    void statsChanged3(VlcStats *stats);

};

#endif // CODECCOMPAREWINDOW_H
