#include "OpenCVUtils.h"

OpenCVUtils::OpenCVUtils() {}

QImage OpenCVUtils::cvMatToQImage(const cv::Mat &inMat) {
    switch (inMat.type()) {
    // 8-bit, 4 channel
    case CV_8UC4: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_ARGB32);

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_RGB888);

        return image.rgbSwapped();
    }

    // 8-bit, 1 channel
    case CV_8UC1: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Grayscale8);

        return image;
    }

    case CV_32F: {
        QImage image(inMat.data, inMat.cols, inMat.rows, static_cast<int>(inMat.step), QImage::Format_Grayscale8);

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
        break;
    }

    return QImage();
}

QPixmap OpenCVUtils::cvMatToQPixmap(const cv::Mat &inMat) { return QPixmap::fromImage(cvMatToQImage(inMat)); }

cv::Mat OpenCVUtils::QImageToCvMat(const QImage &inImage, bool inCloneImageData) {
    switch (inImage.format()) {
    // 8-bit, 4 channel
    case QImage::Format_ARGB32:
    case QImage::Format_ARGB32_Premultiplied: {
        cv::Mat mat(inImage.height(), inImage.width(), CV_8UC4, const_cast<uchar *>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine()));

        return (inCloneImageData ? mat.clone() : mat);
    }

    // 8-bit, 3 channel
    case QImage::Format_RGB32:
    case QImage::Format_RGB888: {
        if (!inCloneImageData) {
            qWarning() << "ASM::QImageToCvMat() - Conversion requires cloning because we use a temporary QImage";
        }

        QImage swapped = inImage;

        if (inImage.format() == QImage::Format_RGB32) {
            swapped = swapped.convertToFormat(QImage::Format_RGB888);
        }

        swapped = swapped.rgbSwapped();

        return cv::Mat(swapped.height(), swapped.width(), CV_8UC3, const_cast<uchar *>(swapped.bits()),
                       static_cast<size_t>(swapped.bytesPerLine()))
            .clone();
    }

    // 8-bit, 1 channel
    case QImage::Format_Indexed8: {
        cv::Mat mat(inImage.height(), inImage.width(), CV_8UC1, const_cast<uchar *>(inImage.bits()),
                    static_cast<size_t>(inImage.bytesPerLine()));

        return (inCloneImageData ? mat.clone() : mat);
    }

    default:
        qWarning() << "ASM::QImageToCvMat() - QImage format not handled in switch:" << inImage.format();
        break;
    }

    return cv::Mat();
}

// If inPixmap exists for the lifetime of the resulting cv::Mat, pass false to inCloneImageData to share inPixmap's data
// with the cv::Mat directly
//    NOTE: Format_RGB888 is an exception since we need to use a local QImage and thus must clone the data regardless
cv::Mat OpenCVUtils::QPixmapToCvMat(const QPixmap &inPixmap, bool inCloneImageData) {
    return QImageToCvMat(inPixmap.toImage(), inCloneImageData);
}
