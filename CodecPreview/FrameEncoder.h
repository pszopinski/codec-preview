#ifndef FRAMEENCODER_H
#define FRAMEENCODER_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <opencv2/opencv.hpp>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
}

class FrameEncoder {
private:
    const AVRational dstFps = {30, 1};
    const int dstWidth = 640;
    const int dstHeight = 480;
    AVFormatContext *outctx;
    AVCodec *vcodec;
    AVStream *vstrm;
    SwsContext *swsctx;
    AVFrame *frame;
    std::vector<uint8_t> frameBuf;
    int64_t framePts;
    unsigned nbFrames;
    bool endOfStream;
    int gotPkt;
    const char *outFile;
public:
    FrameEncoder();
    void onInit(cv::VideoCapture *capture, const char *fileName);
    void onLoop(cv::Mat image);
    void onFinish();
};

#endif // FRAMEENCODER_H
