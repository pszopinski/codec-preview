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
#include <VLCQtCore/Stats.h>


namespace Ui {
class CodecComparisonWindow;
}

class CodecComparisonWindow : public QMainWindow
{
    Q_OBJECT
    QProcess process;
    QProcess framesProbe;

private:
    VlcInstance *vlcInstance;
    VlcMedia *vlcMedia;
    VlcMediaPlayer *vlcPlayer;
    VlcWidgetVolumeSlider *vlcVolume;

    VlcInstance *vlcInstanceEncoded;
    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;
    VlcWidgetVolumeSlider *vlcVolumeEncoded;

    QQueue<char> typesOfFrames;


public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();

    void openLocal();
    void openCamera();
    void closeEvent(QCloseEvent *event);


private slots:
    void on_actionOpen_file_triggered();

    void on_actionOpen_camera_triggered();

    void readOutput();



private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
