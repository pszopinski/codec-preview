#ifndef VIDEOINFOWIDGET_H
#define VIDEOINFOWIDGET_H

#include <fstream>


#include <QWidget>
#include <QLineEdit>
#include <QProcess>
#include <QQueue>
#include <QDebug>


#include "constants.h"

namespace Ui {
class VideoInfoWidget;
}

class VideoInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoInfoWidget(QWidget *parent = 0);
    ~VideoInfoWidget();
    void stopProbe();
    void clearFrameQueue();
    void startFrameProbe(QString command);
    void startStreamProbe(QString command);

private:
    QProcess frameProbeProcess;
    QProcess streamProbeProcess;
    QQueue<char> framesQueue;

private:
    Ui::VideoInfoWidget *ui;

private slots:
  void parseFrameProbeOutput();
  void parseStreamProbeOutput(int a, QProcess::ExitStatus b);
};

#endif // VIDEOINFOWIDGET_H
