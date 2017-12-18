#include "MainWindow.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[]) {
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    // read an image
    // cv::Mat image = cv::imread("c://singleframe.jpg", 1);
    // create image window named "My Image"
    // cv::namedWindow("My Image");
    // show the image on window
    // cv::imshow("My Image", image);

    return a.exec();
}
