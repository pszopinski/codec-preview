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
}

MacroblocksWindow::~MacroblocksWindow() { delete ui; }
