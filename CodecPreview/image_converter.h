#ifndef IMAGECONVERTER_H
#define IMAGECONVERTER_H

//Qt Headers
#include <QImage>
#include <QPixmap>

//OpenCV Headers
#include <opencv2/opencv.hpp>

class ImageConverter
{
public:
    static QImage cvMatToQImage(const cv::Mat &inMat);
    static QPixmap cvMatToQPixmap(const cv::Mat &inMat);
};

#endif // IMAGECONVERTER_H
