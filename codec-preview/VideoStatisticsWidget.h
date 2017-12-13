#ifndef VIDEOSTATISTICSWIDGET_H
#define VIDEOSTATISTICSWIDGET_H

#include <fstream>

#include <QDebug>
#include <QLineEdit>
#include <QProcess>
#include <QQueue>
#include <QTimer>
#include <QWidget>
#include <VLCQtCore/Stats.h>

#include "ParameterManager.h"
#include "constants.h"

namespace Ui {
class VideoStatisticsWidget;
}

class VideoStatisticsWidget : public QWidget {
    Q_OBJECT

  private:
    QProcess frameProbeProcess;
    QProcess streamProbeProcess;
    QQueue<char> framesQueue;
    ParameterManager paramManager;
    QTimer *timer;                    // timer  - reading bitrate
    int interval;                     // timer interval
    QString getBitrate(QString line); // parsing a one line from a file

  public:
    Ui::VideoStatisticsWidget *ui;

    explicit VideoStatisticsWidget(QWidget *parent = 0);
    ~VideoStatisticsWidget();
    void stopProbe();
    void clearFrameQueue();
    void startFrameProbe(QString command);
    void startStreamProbe(QString command);
    void setFrameTypeText(QString text);
    QSize getFrameSize();

  private slots:
    void parseFrameProbeOutput();
    void parseStreamProbeOutput(int a, QProcess::ExitStatus b);
    void updateBitrate(); // it is called by the timer

  public slots:
    void onStatsChange(VlcStats *stats);
};

#endif // VIDEOSTATISTICSWIDGET_H
