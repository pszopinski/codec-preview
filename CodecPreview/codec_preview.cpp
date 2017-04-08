#include "codec_preview.h"
#include "ui_codec_preview.h"
#include <fstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

CodecPreview::CodecPreview(QWidget *parent) {

    parent = new QMainWindow(parent);
    ui = new Ui::CodecPreview();
    //cap = cv::VideoCapture(0);
    cap = cv::VideoCapture("C:/Users/Professional/Desktop/Pulpit-mniej wazne/2ff4fd89db3f1a57fda90bc49c0f30d2.mp4");
    if( !cap.isOpened() )
            std::cout<<"Blad";

    ui->setupUi(this);
    imgbuf = std::vector<uint8_t>(dst_height * dst_width * 3 + 16);
    image = cv::Mat(dst_height, dst_width, CV_8UC3, imgbuf.data(), dst_width * 3);

    encoder.onInit(&cap, "output.mp4");

    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    _timer.start(16);
}

void CodecPreview::on_timeout() {
    /*
    if (!cap.isOpened())
        exit(-1);
        */

    //cap >> image;
    cap >> image;
    if(image.empty()) cap = cv::VideoCapture("C:/Users/Professional/Desktop/Pulpit-mniej wazne/2ff4fd89db3f1a57fda90bc49c0f30d2.mp4");
    /*
    image = cv::imread("C:/Users/Professional/Desktop/tlo.png", CV_LOAD_IMAGE_COLOR);
    if(! image.data )                              // Check for invalid input
       {
           std::cout <<  "Could not open or find the image" << std::endl ;
           return ;
       }
*/
    encoder.onLoop(image);


    QPixmap framePixmap = ImageConverter::cvMatToQPixmap(image);
    QPixmap framePixmap2 = ImageConverter::cvMatToQPixmap(image);
    int w = ui->rawVideo->width();
    int h = ui->rawVideo->height();
    int w2 = ui->encodedVideo->width();
    int h2 = ui->encodedVideo->height();
    ui->rawVideo->setPixmap(framePixmap.scaled(w, h, Qt::KeepAspectRatio));
    ui->encodedVideo->setPixmap(framePixmap2.scaled(w2, h2, Qt::KeepAspectRatio));
}

CodecPreview::~CodecPreview() { delete ui; }



void CodecPreview::on_pushButton_clicked()
{
    encoder.onFinish();

}
