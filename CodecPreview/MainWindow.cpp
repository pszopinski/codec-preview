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
    //encodedPlayer = new Player();
    tcpReceiver = new TcpReceiver();

    QObject::connect(rawPlayer, SIGNAL(processedImage(QImage)),
                              this, SLOT(updateRawPlayerUi(QImage)));

    QObject::connect(tcpReceiver, SIGNAL(imageReceived(QImage)), this, SLOT(updateEncodedPlayerUi(QImage)));

    ui->setupUi(this);


}


MainWindow::~MainWindow() {
    delete rawPlayer;
    //delete encodedPlayer;
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
    //encodedPlayer->stopCamera();

    QString fileName = QFileDialog::getOpenFileName();



    if (!fileName.isEmpty()) {
        if (!rawPlayer->loadVideo(fileName.toUtf8().constData())) {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }


        QString width = QString::number(rawPlayer->getWidth());
        QString height = QString::number(rawPlayer->getHeight());

        qDebug() << "player width " << fileName;


        QString command = QString("ffmpeg -loglevel quiet -y -i \"" + fileName + "\" -s ") + width + QString("x") + height + QString(" -vcodec mjpeg -f nut - | ffmpeg -f nut -i - -vcodec rawvideo -vf format=pix_fmts=rgb24 -pixel_format rgb24 -f rawvideo tcp://localhost:2000 2>NUL");
        cmdThread.runCommand(command.toUtf8().constData());

        tcpReceiver->start(rawPlayer->getWidth(), rawPlayer->getHeight());

        rawPlayer->play();
    }
}

void MainWindow::on_actionCamera_triggered() {
    bool ret;
    ret = rawPlayer->startCamera(0);
    if(!ret) std::cout << "Error starting the raw camera" << std::endl;

    rawPlayer->play();
}


