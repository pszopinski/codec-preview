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

public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();

    void openLocal();

private slots:
    void on_actionOpen_file_triggered();

private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
