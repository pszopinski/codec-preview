#ifndef CODECCOMPARISONWINDOW_H
#define CODECCOMPARISONWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QThread>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
#include <VLCQtWidgets/WidgetVolumeSlider.h>

#include "avc.h"
#include "h261.h"
#include "h264.h"
#include "h265.h"
#include "mjpeg.h"
#include "mpeg1.h"
#include "mpeg2.h"

#define CODECS_NUMBER 7


namespace Ui {
class CodecComparisonWindow;
}

class CodecComparisonWindow : public QMainWindow
{
    Q_OBJECT
    QProcess process;

public:
    VlcInstance *vlcInstance;
    VlcMedia *vlcMedia;
    VlcMediaPlayer *vlcPlayer;
    VlcWidgetVolumeSlider *vlcVolume;

    VlcInstance *vlcInstanceEncoded;
    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;
    VlcWidgetVolumeSlider *vlcVolumeEncoded;

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

private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
