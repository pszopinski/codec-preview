#ifndef VIDEOSTATISTICSWIDGET_H
#define VIDEOSTATISTICSWIDGET_H

#include <fstream>

#include <QDebug>
#include <QLineEdit>
#include <QProcess>
#include <QQueue>
#include <QWidget>
#include <VLCQtCore/Stats.h>

#include "constants.h"
#include "ParameterManager.h"

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

  public:
    Ui::VideoStatisticsWidget *ui;

    explicit VideoStatisticsWidget(QWidget *parent = 0);
    ~VideoStatisticsWidget();
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

#endif // VIDEOSTATISTICSWIDGET_H
