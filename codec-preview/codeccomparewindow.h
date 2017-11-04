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

    QLabel *original;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;

    H261Manager* h261Manager = new H261Manager();
    H264Manager* h264Manager = new H264Manager();
    H265Manager* h265Manager = new H265Manager();
    MJPEGManager* mjpegManager = new MJPEGManager();
    MPEG1Manager* mpeg1Manager = new MPEG1Manager();
    MPEG2Manager* mpeg2Manager = new MPEG2Manager();






    private slots:
    void parseFrameProbeOutput0();
    void parseFrameProbeOutput3();
};

#endif // CODECCOMPAREWINDOW_H
