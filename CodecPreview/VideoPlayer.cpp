#include "VideoPlayer.h"

Player::Player(QObject *parent) : QThread(parent) {
    stopVideo = true;
}


bool Player::loadVideo(std::string filename) {
    capture.open(filename);

    if (capture.isOpened()) {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else
        return false;

}



void Player::play() {
    if (!isRunning()) {
        if (isStopped()){
            stopVideo = false;
        }
        start(HighestPriority);
    }
}


void Player::run() {
    int delay;
    if(inputFromCamera) delay = 1000/16;
    else delay = (1000/frameRate);
    while(!stopVideo) {
        if (!capture.read(frame)) {
            stopVideo = true;
        }
        if (frame.channels()== 3) {
            cv::cvtColor(frame, rgbFrame, CV_BGR2RGB);
            image = QImage((const unsigned char*)(rgbFrame.data),
                           rgbFrame.cols,rgbFrame.rows, QImage::Format_RGB888);
        }
        else {
            image = QImage((const unsigned char*)(frame.data),
                           frame.cols,frame.rows, QImage::Format_Indexed8);
        }
        emit processedImage(image);
        this->msleep(delay);
    }
}

Player::~Player() {
    mutex.lock();
    stopVideo = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void Player::stop()
{
    stopVideo = true;
}

void Player::msleep(int ms){
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool Player::isStopped() const{
    return this->stopVideo;
}

bool Player::startCamera(int n) {
    stop();
    inputFromCamera = true;
    capture.open(n);

    if (capture.isOpened())
        return true;
    else
        return false;

}

void Player::stopCamera() {
    stop();
    inputFromCamera = false;
    capture.release();
}

int Player::getWidth() {
    return capture.get(CV_CAP_PROP_FRAME_WIDTH);
}

int Player::getHeight() {
    return capture.get(CV_CAP_PROP_FRAME_HEIGHT);
}
