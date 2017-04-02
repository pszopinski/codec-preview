#ifndef CODECPREVIEW_H
#define CODECPREVIEW_H
#define __STDC_CONSTANT_MACROS

#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include <QTimer>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ffmpeg is a c library, so extern declaration required for c++

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/frame.h"
#include "libavutil/imgutils.h"
#include "libavutil/mem.h"
#include "libswscale/swscale.h"
#include "libavformat/avformat.h"
#include "libavutil/avutil.h"
#include "libavutil/pixdesc.h"
}

namespace Ui {
class CodecPreview;
}

class CodecPreview : public QMainWindow {
  Q_OBJECT
  QTimer _timer;
  cv::VideoCapture cap;

  //variables needed for saving encoded file part
  const char* outfile;
  const AVRational dst_fps = {30, 1};
  const int dst_width = 640;
  const int dst_height = 480;
  std::vector<uint8_t> imgbuf;
  cv::Mat image;
  AVFormatContext* outctx;
  AVCodec* vcodec;
  AVStream* vstrm;
  SwsContext* swsctx;
  AVFrame* frame;
  std::vector<uint8_t> framebuf;
  int64_t frame_pts = 0;
  unsigned nb_frames = 0;
  bool end_of_stream = false;
  int got_pkt = 0;




public:
  explicit CodecPreview(QWidget *parent = 0);
  ~CodecPreview();
  QImage cvMatToQImage(const cv::Mat &inMat);
  QPixmap cvMatToQPixmap(const cv::Mat &inMat);

private:
  Ui::CodecPreview *ui;

private slots:
  void on_timeout();
  void on_pushButton_clicked();
};

#endif // CODECPREVIEW_H
