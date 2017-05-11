#ifndef CODECCOMPARISONWINDOW_H
#define CODECCOMPARISONWINDOW_H

#include <QMainWindow>
#include <QQueue>
#include <QFileDialog>
#include <QDebug>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVolumeSlider.h>

#include "codectabs/h261tab.h"
#include "codectabs/h264tab.h"
#include "codectabs/h265tab.h"
#include "codectabs/mjpegtab.h"
#include "codectabs/mpeg1tab.h"
#include "codectabs/mpeg2tab.h"

#include "constants.h"



namespace Ui {
class CodecComparisonWindow;
}

class CodecComparisonWindow : public QMainWindow
{
    Q_OBJECT
    QProcess encodingProcess;
    QProcess probeProcess;

private:
    VlcInstance *vlcInstance;

    VlcMedia *vlcMediaRaw;
    VlcMediaPlayer *vlcPlayerRaw;
    VlcWidgetVolumeSlider *vlcVolumeRaw;

    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;
    VlcWidgetVolumeSlider *vlcVolumeEncoded;

    QQueue<char> typesOfFrames;

    QString file;

    Codec **codecs;

public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();

    void openLocal();
    void openCamera();
    void closeEvent(QCloseEvent *event);
    void initCodecs();

private slots:
    void on_actionOpen_file_triggered();
    void on_actionOpen_camera_triggered();
    void tabSelected();
    void readOutput();

private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
