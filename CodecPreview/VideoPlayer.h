#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class Player : public QThread {
    Q_OBJECT
private:
    bool stopVideo;
    QMutex mutex;
    QWaitCondition condition;
    cv::Mat frame;
    int frameRate;
    cv::VideoCapture capture;
    cv::Mat rgbFrame;
    QImage image;
    bool inputFromCamera = false;
protected:
    void run();
    void msleep(int ms);
public:
    Player(QObject *parent = 0);
    ~Player();
    bool loadVideo(std::string filename);
    void play();
    void stop();
    bool isStopped() const;
    bool startCamera(int n);
    void stopCamera();
    int getWidth();
    int getHeight();
signals:
    void processedImage(const QImage &image);
};
#endif // VIDEOPLAYER_H
