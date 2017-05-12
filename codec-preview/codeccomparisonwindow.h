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
#include <VLCQtCore/Audio.h>


#include "codectabs/h261manager.h"
#include "codectabs/h264manager.h"
#include "codectabs/h265manager.h"
#include "codectabs/mjpegmanager.h"
#include "codectabs/mpeg1manager.h"
#include "codectabs/mpeg2manager.h"

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

    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;

    QQueue<char> typesOfFrames;

    QString file;

    CodecManager **codecs;

    static QString buildEncodingCommand(QString inputParameters, QString inputLocation, QVector<QString> outputPrameters, QVector<QString> outputLocations);
    static QString buildProbeCommand(QString location);


public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();

    void openLocal();
    void openCamera();
    void closeEvent(QCloseEvent *event);
    void initCodecs();
    void broadcast(QString inputParameters, QString inputLocation, QString encodingParameters);

private slots:
    void on_actionOpen_file_triggered();
    void on_actionOpen_camera_triggered();
    void tabSelected();
    void readOutput();

private:
    Ui::CodecComparisonWindow *ui;
};

#endif // CODECCOMPARISONWINDOW_H
