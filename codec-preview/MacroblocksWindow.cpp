#include "MacroblocksWindow.h"
#include "ui_MacroblocksWindow.h"

MacroblocksWindow::MacroblocksWindow(QPixmap *macroblockPixmap, QWidget *parent)
    : QWidget(parent), ui(new Ui::MacroblocksWindow) {
    ui->setupUi(this);
    insertGraphic(ui->macroblockView, macroblockPixmap, 20);

    cv::Mat macroblockImage = OpenCVUtils::QPixmapToCvMat(QPixmap(*macroblockPixmap));
    cv::Mat greyImage;
    cv::cvtColor(macroblockImage, greyImage, cv::COLOR_BGR2GRAY);

    greyImage.convertTo(greyImage, CV_32F);

    cv::Mat dctImage;
    cv::dct(greyImage, dctImage);

    QPixmap dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->dctMacroblockView, &dctPixmap, 20);

    cv::Mat outputImage;
    QPixmap outputPixmap;

    cv::Mat channels[3];
    cv::split(macroblockImage, channels);

    outputImage = computeSingleChannel(macroblockImage, 0, channels);
    outputPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    insertGraphic(ui->yView, &outputPixmap, 20);
    outputImage = computeSingleChannel(macroblockImage, 1, channels);
    outputPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    insertGraphic(ui->crView, &outputPixmap, 10);
    outputImage = computeSingleChannel(macroblockImage, 2, channels);
    outputPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    insertGraphic(ui->cbView, &outputPixmap, 10);
}

MacroblocksWindow::~MacroblocksWindow() { delete ui; }

void MacroblocksWindow::insertGraphic(QGraphicsView *graphicsView, QPixmap *pixmap, int scale) {
    QGraphicsScene *scene = new QGraphicsScene();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(*pixmap);
    scene->addItem(item);
    graphicsView->setScene(scene);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->scale(scale, scale);
}

cv::Mat MacroblocksWindow::computeSingleChannel(cv::Mat inputImage, int channelNum, cv::Mat channels[]) {
    cv::Mat outputImage;
    cv::Mat aux[3];
    double scalar[3][3] = {{1, 127.5, 127.5}, {127.5, 1, 127.5}, {127.5, 127.5, 1}};
    aux[0] = cv::Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[channelNum][0];
    aux[1] = cv::Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[channelNum][1];
    aux[2] = cv::Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[channelNum][2];
    aux[channelNum] = channels[channelNum];
    cv::merge(aux, 3, outputImage);
    cv::cvtColor(outputImage, outputImage, cv::COLOR_BGR2YCrCb);
    outputImage = channels[channelNum];
    return outputImage;
}
