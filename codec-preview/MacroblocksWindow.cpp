#include "MacroblocksWindow.h"
#include "ui_MacroblocksWindow.h"

MacroblocksWindow::MacroblocksWindow(QPixmap *macroblockPixmap, QWidget *parent)
    : QWidget(parent), ui(new Ui::MacroblocksWindow) {
    ui->setupUi(this);
    insertGraphic(ui->macroblockView, macroblockPixmap, 15);

    cv::Mat macroblockImage = OpenCVUtils::QPixmapToCvMat(QPixmap(*macroblockPixmap));

    qDebug() << macroblockPixmap->width();
    qDebug() << macroblockPixmap->height();

    /*
    cv::Mat greyImage;
    cv::cvtColor(macroblockImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::Mat dctImage;
    cv::dct(greyImage, dctImage);
    QPixmap dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->dctMacroblockView, &dctPixmap, 20);

*/
    cv::Mat channels[3];
    cv::split(macroblockImage, channels);

    cv::Mat outputImage;
    QPixmap outputPixmap;

    outputImage = computeSingleChannel(macroblockImage, 0, channels);
    outputPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    macroblockPixmapPart1 = outputPixmap.copy(0, 0, 8, 8);
    macroblockPixmapPart2 = outputPixmap.copy(8, 0, 8, 8);
    macroblockPixmapPart3 = outputPixmap.copy(0, 8, 8, 8);
    macroblockPixmapPart4 = outputPixmap.copy(8, 8, 8, 8);
    insertGraphic(ui->yView1, &macroblockPixmapPart1, 15);
    insertGraphic(ui->yView2, &macroblockPixmapPart2, 15);
    insertGraphic(ui->yView3, &macroblockPixmapPart3, 15);
    insertGraphic(ui->yView4, &macroblockPixmapPart4, 15);

    outputImage = computeSingleChannel(macroblockImage, 1, channels);
    QPixmap macroblockCrComponent = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    insertGraphic(ui->crView, &macroblockCrComponent, 7);
    outputImage = computeSingleChannel(macroblockImage, 2, channels);
    QPixmap macroblockCbComponent = QPixmap(OpenCVUtils::cvMatToQPixmap(outputImage));
    insertGraphic(ui->cbView, &macroblockCbComponent, 7);

    cv::Mat greyImage;
    cv::Mat dctImage;
    QPixmap dctPixmap;
    cv::Mat inputImage;

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockPixmapPart1);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->yView1_dct, &dctPixmap, 15);

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockPixmapPart2);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->yView2_dct, &dctPixmap, 15);

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockPixmapPart3);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->yView3_dct, &dctPixmap, 15);

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockPixmapPart4);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->yView4_dct, &dctPixmap, 15);

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockCrComponent);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->crView_dct, &dctPixmap, 7);

    inputImage = OpenCVUtils::QPixmapToCvMat(macroblockCbComponent);
    cv::cvtColor(inputImage, greyImage, cv::COLOR_BGR2GRAY);
    greyImage.convertTo(greyImage, CV_32F);
    cv::dct(greyImage, dctImage);
    dctPixmap = QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));
    insertGraphic(ui->cbView_dct, &dctPixmap, 7);
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
