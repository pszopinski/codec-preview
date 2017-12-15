#ifndef VIDEOSTATISTICSWIDGET_H
#define VIDEOSTATISTICSWIDGET_H

#include <fstream>

#include <QDebug>
#include <QLineEdit>
#include <QProcess>
#include <QQueue>
#include <QTimer>
#include <QWidget>
#include <QtMath>
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
    int getOut(QString line);
    QString getDelay(QString *lines,
                     const int OUTS); // parameter is array of lines; return delay between raw and encoded
    const int MIN_LENGTH_LINE =
        130; // minimal length of proper line in statistics.txt (vstats_file statistics.txt - in ffmpeg command)

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
    void updateStats(); // it is called by the timer; bitrate and delay

  public slots:
    void onStatsChange(VlcStats *stats);
};

#endif // VIDEOSTATISTICSWIDGET_H
