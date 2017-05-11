#ifndef CODECCOMPARISONWINDOW_H
#define CODECCOMPARISONWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QThread>
#include <QDebug>
#include <QQueue>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVolumeSlider.h>

#include "h261Tab.h"
#include "h264Tab.h"
#include "h265Tab.h"
#include "mjpegTab.h"
#include "mpeg1Tab.h"
#include "mpeg2Tab.h"

#define CODECS_NUMBER 6


namespace Ui {
class CodecComparisonWindow;
}

class CodecComparisonWindow : public QMainWindow
{
    Q_OBJECT
    QProcess process;
    QProcess framesProbe;

public:
    VlcInstance *vlcInstance;
    VlcMedia *vlcMedia;
    VlcMediaPlayer *vlcPlayer;
    VlcWidgetVolumeSlider *vlcVolume;

    VlcInstance *vlcInstanceEncoded;
    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;
    VlcWidgetVolumeSlider *vlcVolumeEncoded;

    QQueue<char> typesOfFrames;

    QTabWidget *tabWidget;
    QString file = NULL;
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

    //void on_AVC_destroyed();

    void readOutput();

private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
