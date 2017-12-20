#ifndef MACROBLOCKSWINDOW_H
#define MACROBLOCKSWINDOW_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QWidget>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "OpenCVUtils.h"

namespace Ui {
class MacroblocksWindow;
}

class MacroblocksWindow : public QWidget {
    Q_OBJECT

  public:
    explicit MacroblocksWindow(QPixmap *macroblockPixmap, QWidget *parent = 0);
    ~MacroblocksWindow();

  private:
    static void insertGraphic(QGraphicsView *graphicsView, QPixmap *pixmap, int scale);
    static cv::Mat computeSingleChannel(cv::Mat inputImage, int channelNum, cv::Mat channels[]);

  private:
    Ui::MacroblocksWindow *ui;
};

#endif // MACROBLOCKSWINDOW_H
