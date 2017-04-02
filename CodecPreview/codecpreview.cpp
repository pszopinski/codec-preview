#include "codecpreview.h"
#include "ui_codecpreview.h"


CodecPreview::CodecPreview(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::CodecPreview), cap(0) {
  ui->setupUi(this);

  //encoding init////////////////
  outfile = "output.mp4";

  av_register_all();
  av_log_set_level(AV_LOG_DEBUG);

  cap.set(cv::CAP_PROP_FRAME_WIDTH, dst_width);
  cap.set(cv::CAP_PROP_FRAME_HEIGHT, dst_height);

  imgbuf = std::vector<uint8_t>(dst_height * dst_width * 3 + 16);
  image = cv::Mat(dst_height, dst_width, CV_8UC3, imgbuf.data(), dst_width * 3);

  outctx = nullptr;

  avformat_alloc_output_context2(&outctx, nullptr, nullptr, outfile);
  avio_open2(&outctx->pb, outfile, AVIO_FLAG_WRITE, nullptr, nullptr);

  vcodec = avcodec_find_encoder(outctx->oformat->video_codec);
  vstrm = avformat_new_stream(outctx, vcodec);

  avcodec_get_context_defaults3(vstrm->codec, vcodec);
  vstrm->codec->width = dst_width;
  vstrm->codec->height = dst_height;
  vstrm->codec->pix_fmt = vcodec->pix_fmts[0];
  vstrm->codec->time_base = vstrm->time_base = av_inv_q(dst_fps);
  vstrm->r_frame_rate = vstrm->avg_frame_rate = dst_fps;
  if (outctx->oformat->flags & AVFMT_GLOBALHEADER)
      vstrm->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

  // open video encoder
  avcodec_open2(vstrm->codec, vcodec, nullptr);

  swsctx = sws_getCachedContext(
      nullptr, dst_width, dst_height, AV_PIX_FMT_BGR24,
      dst_width, dst_height, vstrm->codec->pix_fmt, SWS_BICUBIC, nullptr, nullptr, nullptr);

  frame = av_frame_alloc();
  framebuf = std::vector<uint8_t>(avpicture_get_size(vstrm->codec->pix_fmt, dst_width, dst_height));
  avpicture_fill(reinterpret_cast<AVPicture*>(frame), framebuf.data(), vstrm->codec->pix_fmt, dst_width, dst_height);
  frame->width = dst_width;
  frame->height = dst_height;
  frame->format = static_cast<int>(vstrm->codec->pix_fmt);

  avformat_write_header(outctx, nullptr);

  //encoding init end///////////////


  connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
  _timer.start(16);
}

void CodecPreview::on_timeout() {
  if (!cap.isOpened()) // check if we succeeded
    exit(-1);

  cap >> image;

  //encode loop/////////////
  if (!end_of_stream) {
      // convert cv::Mat(OpenCV) to AVFrame(FFmpeg)
      const int stride[] = { static_cast<int>(image.step[0]) };
      sws_scale(swsctx, &image.data, stride, 0, image.rows, frame->data, frame->linesize);
      frame->pts = frame_pts++;

      // encode video frame
      AVPacket pkt;
      pkt.data = nullptr;
      pkt.size = 0;
      av_init_packet(&pkt);
      avcodec_encode_video2(vstrm->codec, &pkt, end_of_stream ? nullptr : frame, &got_pkt);

      if (got_pkt) {
          // rescale packet timestamp
          pkt.duration = 1;
          av_packet_rescale_ts(&pkt, vstrm->codec->time_base, vstrm->time_base);
          // write packet
          av_write_frame(outctx, &pkt);
          //std::cout << nb_frames << '\r' << std::flush;  // dump progress
          ++nb_frames;
      }
      av_free_packet(&pkt);


  }
  //encode loop end/////////////

  QPixmap framePixmap = cvMatToQPixmap(image);
  ui->rawVideo->setPixmap(framePixmap);
  ui->encodedVideo->setPixmap(framePixmap);
}

CodecPreview::~CodecPreview() { delete ui; }

QImage CodecPreview::cvMatToQImage(const cv::Mat &inMat) {

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

QPixmap CodecPreview::cvMatToQPixmap(const cv::Mat &inMat) {
  return QPixmap::fromImage(cvMatToQImage(inMat));
}

void CodecPreview::on_pushButton_clicked()
{
    //encode finish////////////
    av_write_trailer(outctx);
    //std::cout << nb_frames << " frames encoded" << std::endl;

    av_frame_free(&frame);
    avcodec_close(vstrm->codec);
    avio_close(outctx->pb);
    avformat_free_context(outctx);

    end_of_stream = true;

    //encode finish end////////////
}
