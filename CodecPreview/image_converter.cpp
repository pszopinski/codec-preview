#include "image_converter.h"


QImage ImageConverter::cvMatToQImage(const cv::Mat &inMat) {

    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_ARGB32);

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_RGB888);

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1: {
        QImage image(inMat.data, inMat.cols, inMat.rows,
                     static_cast<int>(inMat.step), QImage::Format_Grayscale8);

        return image;
    }
    }
    return QImage();
}

QPixmap ImageConverter::cvMatToQPixmap(const cv::Mat &inMat) {
    return QPixmap::fromImage(cvMatToQImage(inMat));
}
