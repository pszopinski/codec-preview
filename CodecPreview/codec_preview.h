#ifndef CODECPREVIEW_H
#define CODECPREVIEW_H
#define __STDC_CONSTANT_MACROS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Qt Headers
#include <QMainWindow>
#include <QTimer>

//OpenCV Headers
#include <opencv2/opencv.hpp>


#include "frame_encoder.h"
#include "image_converter.h"


namespace Ui {
class CodecPreview;
}

class CodecPreview : public QMainWindow {
    Q_OBJECT
    QTimer _timer;
    cv::VideoCapture cap;
    const int dst_width = 640;
    const int dst_height = 480;
    std::vector<uint8_t> imgbuf;
    cv::Mat image;
    FrameEncoder encoder;



public:
    explicit CodecPreview(QWidget *parent = 0);
    ~CodecPreview();


private:
    Ui::CodecPreview *ui;

private slots:
    void on_timeout();
    void on_pushButton_clicked();
};

#endif // CODECPREVIEW_H
