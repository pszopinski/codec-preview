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

  public:
    explicit CodecCompareWindow(QWidget *parent = 0);
    ~CodecCompareWindow();
    void stream(QString streamingCommand);
    void closeEvent(QCloseEvent *event);

    QLabel *original;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
};

#endif // CODECCOMPAREWINDOW_H
