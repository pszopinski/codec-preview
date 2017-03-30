#include "camwindow.h"
#include "ui_camwindow.h"

#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

CamWindow::CamWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CamWindow),
    cap(0)
{
    ui->setupUi(this);

    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    // populate your window with images, labels, etc. here
    _timer.start(16);


    //image.load("C:/myimage.png");
    //scene = new QGraphicsScene(this);
    //scene->addPixmap(image);
    //scene->setSceneRect(image.rect());

    scene = new QGraphicsScene(this);



}

void CamWindow::on_timeout() {
    if(!cap.isOpened())  // check if we succeeded
        exit(-1);

    Mat frame;
    cap >> frame; // get a new frame from camera
    //cvtColor(frame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    //Canny(edges, edges, 0, 30, 3);
    //imshow("edges", edges);
    //cout << "hello" << endl;


//    scene->clear();
//    scene->deleteLater();


    QPixmap framePixmap = cvMatToQPixmap(frame);
//    scene->addPixmap(framePixmap);
//    scene->setSceneRect(image.rect());

//    ui->framesView->setScene(scene);
    ui->label_1->setPixmap(framePixmap);
    ui->label_2->setPixmap(framePixmap);

//    ui->framesView2->setScene(scene);

//    if(old_scene != NULL) delete old_scene;
//    old_scene = scene;

}

CamWindow::~CamWindow()
{
    delete ui;
}


QImage CamWindow::cvMatToQImage( const cv::Mat &inMat )
   {
      switch ( inMat.type() )
      {
         // 8-bit, 4 channel
         case CV_8UC4:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_ARGB32 );

            return image;
         }

         // 8-bit, 3 channel
         case CV_8UC3:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_RGB888 );

            return image.rgbSwapped();
         }

         // 8-bit, 1 channel
         case CV_8UC1:
         {
            QImage image( inMat.data,
                          inMat.cols, inMat.rows,
                          static_cast<int>(inMat.step),
                          QImage::Format_Grayscale8 );

            return image;
      }

      }
      return QImage();
}

QPixmap CamWindow::cvMatToQPixmap( const cv::Mat &inMat )
{
   return QPixmap::fromImage( cvMatToQImage( inMat ) );
}
