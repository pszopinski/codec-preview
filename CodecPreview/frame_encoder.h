#ifndef FRAMEENCODER_H
#define FRAMEENCODER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//OpenCV Headers
#include <opencv2/opencv.hpp>

//FFMPEG Headers
extern "C" { //ffmpeg is a c library, so extern declaration required for c++
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

class FrameEncoder
{
private:

    const AVRational dst_fps = {30, 1};
    const int dst_width = 640;
    const int dst_height = 480;
    AVFormatContext *outctx;
    AVCodec *vcodec;
    AVStream *vstrm;
    SwsContext *swsctx;
    AVFrame *frame;
    std::vector<uint8_t> framebuf;
    int64_t frame_pts;
    unsigned nb_frames;
    bool end_of_stream;
    int got_pkt;

    const char *outfile;
public:
    FrameEncoder();
    void onInit(cv::VideoCapture *cap, const char *filename);
    void onLoop(cv::Mat image);
    void onFinish();
};

#endif // FRAMEENCODER_H
