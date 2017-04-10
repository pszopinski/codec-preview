#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define __STDC_CONSTANT_MACROS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <QMainWindow>
#include <QTimer>
#include <QFileDialog>

#include <opencv2/opencv.hpp>

#include "ImageConverter.h"
#include "VideoPlayer.h"
#include "TcpReceiver.h"
#include "CmdThread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    QTimer timer;
    cv::VideoCapture capture;
    std::vector<uint8_t> imgBuf;
    cv::Mat image;
    std::string fileName = "";
    bool playVideo = false;
    bool getCameraInput = false;
    Ui::MainWindow *ui;
    Player* rawPlayer;
    Player* encodedPlayer;
    CmdThread cmdThread;
    TcpReceiver* tcpReceiver;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void updateRawPlayerUi(QImage img);
    void updateEncodedPlayerUi(QImage img);
    void on_actionOpen_triggered();
    void on_actionCamera_triggered();
};

#endif // MAINWINDOW_H
