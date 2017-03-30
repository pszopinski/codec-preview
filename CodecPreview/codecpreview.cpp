#include "codecpreview.h"
#include "ui_codecpreview.h"

CodecPreview::CodecPreview(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CodecPreview), cap(0) {
  ui->setupUi(this);

  connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
  _timer.start(16);
}

void CodecPreview::on_timeout() {
  if (!cap.isOpened()) // check if we succeeded
    exit(-1);

  Mat frame;
  cap >> frame;
  QPixmap framePixmap = cvMatToQPixmap(frame);
  ui->rawVideo->setPixmap(framePixmap);
  ui->encodedVideo->setPixmap(framePixmap);
}

CodecPreview::~CodecPreview() { delete ui; }

QImage CodecPreview::cvMatToQImage(const Mat &inMat) {
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

QPixmap CodecPreview::cvMatToQPixmap(const Mat &inMat) {
  return QPixmap::fromImage(cvMatToQImage(inMat));
}
