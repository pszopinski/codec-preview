#ifndef CODECCOMPARISONWINDOW_H
#define CODECCOMPARISONWINDOW_H

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QProcess>
#include <QQueue>
#include <QVector>
#include <QPushButton>

#include <VLCQtCore/Audio.h>
#include <VLCQtCore/Common.h>
#include <VLCQtCore/Enums.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
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

class CodecComparisonWindow : public QMainWindow {
    Q_OBJECT
public:
    QProcess streamingProcess;
    QProcess probeProcess;

  public:
    Ui::CodecComparisonWindow *ui;
    VlcInstance *vlcInstance;

    VlcMedia *vlcMediaRaw;
    VlcMediaPlayer *vlcPlayerRaw;

    VlcMedia *vlcMediaEncoded;
    VlcMediaPlayer *vlcPlayerEncoded;

    QQueue<char> typesOfFrames;

    QString inputParameters;
    QString inputLocation;
    bool selectedCodecs[6];
    //ShowCodecs ShowCodecs;

    QVector<CodecManager *> codecManagers;
public:
    static QString buildStreamingCommand(QString inputParameters,
                                         QString inputLocation,
                                         QVector<QString> outputPrameters,
                                         QVector<QString> outputLocations);
    static QString buildProbeCommand(QString location);

  public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();
    void closeEvent(QCloseEvent *event);
    void initCodecs();
    void initVlc();
    void connectSlots();
    void setSelectedCodecs(bool b[]);
    QVector<CodecManager *> getCodecManagers();

  private slots:
    void readOutput();
    //void readOutput2();
    void on_actionOpenFile_triggered();
    void on_actionOpenCamera_triggered();
    void broadcast();

    void on_compareCodecs_clicked();

signals:
    void settingsChanged();
};

#endif // CODECCOMPARISONWINDOW_H
