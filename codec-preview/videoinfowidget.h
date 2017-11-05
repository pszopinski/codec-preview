#ifndef VIDEOINFOWIDGET_H
#define VIDEOINFOWIDGET_H

#include <fstream>

#include <QDebug>
#include <QLineEdit>
#include <QProcess>
#include <QQueue>
#include <QWidget>
#include <VLCQtCore/Stats.h>

#include "constants.h"
#include "parammanager.h"

namespace Ui {
class VideoInfoWidget;
}

class VideoInfoWidget : public QWidget {
    Q_OBJECT

  private:
    QProcess frameProbeProcess;
    QProcess streamProbeProcess;
    QQueue<char> framesQueue;
    ParamManager paramManager;

  public:
    Ui::VideoInfoWidget *ui;

    explicit VideoInfoWidget(QWidget *parent = 0);
    ~VideoInfoWidget();
    void stopProbe();
    void clearFrameQueue();
    void startFrameProbe(QString command);
    void startStreamProbe(QString command);
    void setFrameTypeText(QString text);

  private slots:
    void parseFrameProbeOutput();
    void parseStreamProbeOutput(int a, QProcess::ExitStatus b);

  public slots:
    void onStatsChange(VlcStats *stats);
};

#endif // VIDEOINFOWIDGET_H
