#ifndef CAMWINDOW_H
#define CAMWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QGraphicsScene>
#include <QLabel>
#include "opencv2/opencv.hpp"


#ifdef __cplusplus
extern "C" {
#endif
#include <libavcodec/avcodec.h>
#include <libavutil/mathematics.h>
#ifdef __cplusplus
}
#endif

using namespace cv;

namespace Ui {
class CamWindow;
}

class CamWindow : public QMainWindow
{
    Q_OBJECT
    QTimer _timer;
    VideoCapture cap;
    Mat edges;
    QGraphicsScene *scene;
    QPixmap image;
    QGraphicsScene* old_scene;
    QLabel label_1;
    QLabel label_2;

    AVCodec *codec;
    AVCodecContext *c= NULL;
    int i, ret, x, y, got_output;
    FILE *f;
    AVFrame *frame;
    AVPacket pkt;
    uint8_t endcode[4] = { 0, 0, 1, 0xb7 };

public:
    explicit CamWindow(QWidget *parent = 0);
    ~CamWindow();
    QImage cvMatToQImage( const cv::Mat &inMat );
    QPixmap cvMatToQPixmap( const cv::Mat &inMat );

private slots:
    void on_timeout();

private:
    Ui::CamWindow *ui;
};

#endif // CAMWINDOW_H
