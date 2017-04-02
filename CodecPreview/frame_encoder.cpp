#include "frame_encoder.h"

FrameEncoder::FrameEncoder()
{

}

void FrameEncoder::onInit(cv::VideoCapture *cap, const char *filename)
{
    outfile = filename;

    frame_pts = 0;
    nb_frames = 0;
    end_of_stream = false;
    got_pkt = 0;

    av_register_all();

    cap->set(cv::CAP_PROP_FRAME_WIDTH, dst_width);
    cap->set(cv::CAP_PROP_FRAME_HEIGHT, dst_height);


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
}

void FrameEncoder::onLoop(cv::Mat image)
{
    if (!end_of_stream) {
        const int stride[] = { static_cast<int>(image.step[0]) };
        sws_scale(swsctx, &image.data, stride, 0, image.rows, frame->data, frame->linesize);
        frame->pts = frame_pts++;

        AVPacket pkt;
        pkt.data = nullptr;
        pkt.size = 0;
        av_init_packet(&pkt);
        avcodec_encode_video2(vstrm->codec, &pkt, end_of_stream ? nullptr : frame, &got_pkt);

        if (got_pkt) {
            pkt.duration = 1;
            av_packet_rescale_ts(&pkt, vstrm->codec->time_base, vstrm->time_base);
            av_write_frame(outctx, &pkt);
            ++nb_frames;
        }
        av_free_packet(&pkt);
    }
}

void FrameEncoder::onFinish()
{
    av_write_trailer(outctx);

    av_frame_free(&frame);
    avcodec_close(vstrm->codec);
    avio_close(outctx->pb);
    avformat_free_context(outctx);

    end_of_stream = true;
}
