#ifndef CODECPREVIEW_H
#define CODECPREVIEW_H

#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include <QTimer>

using namespace cv;

namespace Ui {
class CodecPreview;
}

class CodecPreview : public QMainWindow {
  Q_OBJECT
  QTimer _timer;
  VideoCapture cap;

public:
  explicit CodecPreview(QWidget *parent = 0);
  ~CodecPreview();
  QImage cvMatToQImage(const cv::Mat &inMat);
  QPixmap cvMatToQPixmap(const cv::Mat &inMat);

private:
  Ui::CodecPreview *ui;

private slots:
  void on_timeout();
};

#endif // CODECPREVIEW_H
