#include <fstream>
#include <iostream>

#include <QMessageBox>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {

    parent = new QMainWindow(parent);
    ui = new Ui::MainWindow();

    rawPlayer = new Player();
    encodedPlayer = new Player();

    QObject::connect(rawPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updateRawPlayerUi(QImage)));

    QObject::connect(encodedPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updateEncodedPlayerUi(QImage)));

    ui->setupUi(this);
}


MainWindow::~MainWindow() {
    delete rawPlayer;
    delete encodedPlayer;
    delete ui;
}


void MainWindow::updateRawPlayerUi(QImage image)
{
    if (!image.isNull()) {
        ui->rawVideo->setAlignment(Qt::AlignCenter);
        ui->rawVideo->setPixmap(QPixmap::fromImage(image).scaled(ui->rawVideo->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));

    }


}
void MainWindow::updateEncodedPlayerUi(QImage image) {
    if (!image.isNull()) {
        ui->encodedVideo->setAlignment(Qt::AlignCenter);
        ui->encodedVideo->setPixmap(QPixmap::fromImage(image).scaled(ui->encodedVideo->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::on_actionOpen_triggered() {
    rawPlayer->stopCamera();
    encodedPlayer->stopCamera();

    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isEmpty()) {
        if (!rawPlayer->loadVideo(fileName.toUtf8().constData())) {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }

        if (!encodedPlayer->loadVideo(fileName.toUtf8().constData())) {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }


        rawPlayer->play();
        encodedPlayer->play();
    }
}

void MainWindow::on_actionCamera_triggered() {
    bool ret;
    ret = rawPlayer->startCamera(0);
    if(!ret) std::cout << "Error starting the raw camera" << std::endl;
    ret = encodedPlayer->startCamera(0);
    if(!ret) std::cout << "Error starting the encoded camera" << std::endl;

    rawPlayer->play();
    encodedPlayer->play();
}
