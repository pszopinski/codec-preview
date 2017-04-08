#include "FrameEncoder.h"

FrameEncoder::FrameEncoder()
{

}

void FrameEncoder::onInit(cv::VideoCapture *capture, const char *fileName) {
    outFile = fileName;

    framePts = 0;
    nbFrames = 0;
    endOfStream = false;
    gotPkt = 0;

    av_register_all();

    capture->set(cv::CAP_PROP_FRAME_WIDTH, dstWidth);
    capture->set(cv::CAP_PROP_FRAME_HEIGHT, dstHeight);


    outctx = nullptr;

    avformat_alloc_output_context2(&outctx, nullptr, nullptr, outFile);
    avio_open2(&outctx->pb, outFile, AVIO_FLAG_WRITE, nullptr, nullptr);

    vcodec = avcodec_find_encoder(outctx->oformat->video_codec);
    vstrm = avformat_new_stream(outctx, vcodec);

    avcodec_get_context_defaults3(vstrm->codec, vcodec);
    vstrm->codec->width = dstWidth;
    vstrm->codec->height = dstHeight;
    vstrm->codec->pix_fmt = vcodec->pix_fmts[0];
    vstrm->codec->time_base = vstrm->time_base = av_inv_q(dstFps);
    vstrm->r_frame_rate = vstrm->avg_frame_rate = dstFps;
    if (outctx->oformat->flags & AVFMT_GLOBALHEADER)
        vstrm->codec->flags |= AV_CODEC_FLAG_GLOBAL_HEADER;

    avcodec_open2(vstrm->codec, vcodec, nullptr);

    swsctx = sws_getCachedContext(
                nullptr, dstWidth, dstHeight, AV_PIX_FMT_BGR24,
                dstWidth, dstHeight, vstrm->codec->pix_fmt, SWS_BICUBIC, nullptr, nullptr, nullptr);

    frame = av_frame_alloc();
    frameBuf = std::vector<uint8_t>(avpicture_get_size(vstrm->codec->pix_fmt, dstWidth, dstHeight));
    avpicture_fill(reinterpret_cast<AVPicture*>(frame), frameBuf.data(), vstrm->codec->pix_fmt, dstWidth, dstHeight);
    frame->width = dstWidth;
    frame->height = dstHeight;
    frame->format = static_cast<int>(vstrm->codec->pix_fmt);

    avformat_write_header(outctx, nullptr);
}

void FrameEncoder::onLoop(cv::Mat image) {
    if (!endOfStream) {
        const int stride[] = { static_cast<int>(image.step[0]) };
        sws_scale(swsctx, &image.data, stride, 0, image.rows, frame->data, frame->linesize);
        frame->pts = framePts++;

        AVPacket pkt;
        pkt.data = nullptr;
        pkt.size = 0;
        av_init_packet(&pkt);
        avcodec_encode_video2(vstrm->codec, &pkt, endOfStream ? nullptr : frame, &gotPkt);

        if (gotPkt) {
            pkt.duration = 1;
            av_packet_rescale_ts(&pkt, vstrm->codec->time_base, vstrm->time_base);
            av_write_frame(outctx, &pkt);
            ++nbFrames;
        }
        av_free_packet(&pkt);
    }
}

void FrameEncoder::onFinish() {
    av_write_trailer(outctx);

    av_frame_free(&frame);
    avcodec_close(vstrm->codec);
    avio_close(outctx->pb);
    avformat_free_context(outctx);

    endOfStream = true;
}
