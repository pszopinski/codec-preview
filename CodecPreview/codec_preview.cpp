#include "codec_preview.h"
#include "ui_codec_preview.h"

CodecPreview::CodecPreview(QWidget *parent) {

    parent = new QMainWindow(parent);
    ui = new Ui::CodecPreview();
    cap = cv::VideoCapture(0);

    ui->setupUi(this);

    imgbuf = std::vector<uint8_t>(dst_height * dst_width * 3 + 16);
    image = cv::Mat(dst_height, dst_width, CV_8UC3, imgbuf.data(), dst_width * 3);


    encoder.onInit(&cap, "output.mp4");

    connect(&_timer, SIGNAL(timeout()), this, SLOT(on_timeout()));
    _timer.start(16);
}

void CodecPreview::on_timeout() {
    if (!cap.isOpened())
        exit(-1);

    cap >> image;

    encoder.onLoop(image);

    QPixmap framePixmap = ImageConverter::cvMatToQPixmap(image);
    ui->rawVideo->setPixmap(framePixmap);
    ui->encodedVideo->setPixmap(framePixmap);
}

CodecPreview::~CodecPreview() { delete ui; }



void CodecPreview::on_pushButton_clicked()
{
    encoder.onFinish();

}
