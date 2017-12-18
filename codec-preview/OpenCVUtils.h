#ifndef OPENCVUTILS_H
#define OPENCVUTILS_H

#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class OpenCVUtils {
  public:
    OpenCVUtils();
    static QImage cvMatToQImage(const cv::Mat &inMat);
    static QPixmap cvMatToQPixmap(const cv::Mat &inMat);
    static cv::Mat QImageToCvMat(const QImage &inImage, bool inCloneImageData = true);
    static cv::Mat QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData = true);
};

#endif // OPENCVUTILS_H
