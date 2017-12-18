#include "MacroblocksWindow.h"
#include "ui_MacroblocksWindow.h"

MacroblocksWindow::MacroblocksWindow(QPixmap *macroblockPixmap, QWidget *parent)
    : QWidget(parent), ui(new Ui::MacroblocksWindow) {
    ui->setupUi(this);
    this->macroblockPixmap = macroblockPixmap;

    scene = new QGraphicsScene();
    item = new QGraphicsPixmapItem(*macroblockPixmap);
    scene->addItem(item);
    ui->macroblockView->setScene(scene);
    ui->macroblockView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->macroblockView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // ui->macroblockView->fitInView(item);
    ui->macroblockView->scale(40, 40);

    const QPixmap pixmap = QPixmap(*macroblockPixmap);
    macroblockImage = OpenCVUtils::QPixmapToCvMat(pixmap);
    cv::cvtColor(macroblockImage, greyImage, cv::COLOR_BGR2GRAY);

    // macroblockImage.convertTo(convertedImage, CV_32F, 1.0 / 255);
    greyImage.convertTo(greyImage, CV_32F, 1.0 / 255);

    cv::dct(greyImage, dctImage);
    // cv::imshow("result", dctImage);

    dctPixmap = new QPixmap(OpenCVUtils::cvMatToQPixmap(dctImage));

    dctScene = new QGraphicsScene();
    dctItem = new QGraphicsPixmapItem(*dctPixmap);
    dctScene->addItem(dctItem);
    ui->dctMacroblockView->setScene(dctScene);
    ui->dctMacroblockView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->dctMacroblockView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->dctMacroblockView->scale(40, 40);
}

MacroblocksWindow::~MacroblocksWindow() { delete ui; }
