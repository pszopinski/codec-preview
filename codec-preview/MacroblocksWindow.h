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
    Ui::MacroblocksWindow *ui;

    QPixmap *macroblockPixmap;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;

    cv::Mat macroblockImage;
    cv::Mat dctImage;
    cv::Mat greyImage;

    QPixmap *dctPixmap;
    QGraphicsScene *dctScene;
    QGraphicsPixmapItem *dctItem;
};

#endif // MACROBLOCKSWINDOW_H
