#ifndef CODECCOMPARISONWINDOW_H
#define CODECCOMPARISONWINDOW_H

#include <fstream>

#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QProcess>
#include <QPushButton>
#include <QQueue>
#include <QVector>
#include <QThread>

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

#include "showcodecs.h"

#include "constants.h"

namespace Ui {
class CodecComparisonWindow;
}

class CodecComparisonWindow : public QMainWindow {
    Q_OBJECT
  public:
    QProcess streamingProcess;
    QProcess frameProbeProcess;
    QProcess streamProbeProcess;

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
    ShowCodecs showCodecs;

    QVector<CodecManager *> codecManagers;

    static QString parametersToString(QMap<QString, QString> parameters);

  public:
    static QString buildStreamingCommand(QString inputParameters,
                                         QString inputLocation,
                                         QVector<QString> outputPrameters,
                                         QVector<QString> outputLocations);
    static QString buildProbeCommand(QString location, QString params);

  public:
    explicit CodecComparisonWindow(QWidget *parent = 0);
    ~CodecComparisonWindow();
    void closeEvent(QCloseEvent *event);
    void initCodecs();
    void initVlc();
    void connectSlots();
    void setSelectedCodecs(int first, int second, int third);
    QVector<CodecManager *> getCodecManagers();

  private slots:
    void readOutput();

    void on_actionOpenFile_triggered();
    void on_actionOpenCamera_triggered();
    void broadcast();
    void onFinished(int a, QProcess::ExitStatus b);

    void on_compareCodecs_clicked();


    void on_crf_returnPressed();

    void on_crf_editingFinished();

signals:
    void settingsChanged();
};

#endif // CODECCOMPARISONWINDOW_H
