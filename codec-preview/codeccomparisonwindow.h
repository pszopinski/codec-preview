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
#include <VLCQtCore/Stats.h>


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
    Ui::CodecComparisonWindow *ui;
    VlcInstance *vlcInstance;

    VlcMedia *vlcMediaRaw;
    VlcMediaPlayer *vlcPlayerRaw;

    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;

    QQueue<char> typesOfFrames;

    QString inputParameters;
    QString inputLocation;
    QString encodingParameters;

    CodecManager **codecs;

    static QString buildEncodingCommand(QString inputParameters, QString inputLocation, QVector<QString> outputPrameters, QVector<QString> outputLocations);
    static QString buildProbeCommand(QString location);


public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();
    void closeEvent(QCloseEvent *event);
    void initCodecs();
    void broadcast();

private slots:
    void tabSelected();
    void readOutput();

    void on_actionOpenFile_triggered();

    void on_actionOpenCamera_triggered();

signals:
    void settingsChanged();
};

#endif // CODECCOMPARISONWINDOW_H
