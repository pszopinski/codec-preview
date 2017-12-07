#ifndef STATISTICS_H
#define STATISTICS_H

#include <QSize>

class Statistics {
  public:
    Statistics();
    QSize getFrameSize();
    void setFrameSize(QSize frameSize);

  private:
    QSize frameSize;
};

#endif // STATISTICS_H
