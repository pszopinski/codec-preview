#include "mainwindow.h"
#include "selectcodecs.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->codecTabs, &CodecTabsWidget::settingsChanged, this,
            &MainWindow::broadcast);
    connect(ui->codecTabs, &CodecTabsWidget::currentTabChanged, this,
            &MainWindow::broadcast);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::closeEvent(QCloseEvent *event) {
    (void)event; // silence annoying warning

    ui->codecTabs->stopStreaming();
    ui->videoInfo->stopProbe();
}

// void CodecComparisonWindow::on_crf_returnPressed()
//{
//    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
//    settingsChanged();
//}

// void CodecComparisonWindow::on_crf_editingFinished()
//{
//    codecManagers.at(ui->tabWidget->currentIndex())->setCRF(ui->crf->text());
//    settingsChanged();
//}

void MainWindow::on_actionOpen_file_triggered() {

    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Open file"), QDir::homePath(), tr("Multimedia files (*)"),
        Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    ui->codecTabs->openFromFile(filePath);
}

void MainWindow::on_actionOpen_from_camera_triggered() {
    ui->codecTabs->openFromCamera();
}

void MainWindow::on_actionCompare_multiple_codecs_triggered() {
    qDebug() << "Clicked!\n";
    SelectCodecs selectCodecs;
    selectCodecs.setMainWindowHandler(ui->codecTabs);
    selectCodecs.setModal(true);
    selectCodecs.exec();
}

void MainWindow::broadcast() {
    qDebug() << "==========BROADCASTING============";

    ui->codecTabs->getStreamingParameters();

    QString streamingParameters = ui->codecTabs->getStreamingParameters();

    ui->videoInfo->clearFrameQueue();

    // ui->crf->setText(codecManagers.at(ui->tabWidget->currentIndex())->getCRF());

    qDebug() << "Stopping the players...";

    ui->videoPlayback->stopPlayers();

    qDebug() << "Killing current encoding and probe processes...";

    ui->codecTabs->stopStreaming();

    ui->videoInfo->stopProbe();

    ui->codecTabs->startStreaming(streamingParameters);

    QString frameProbeCommand = ui->codecTabs->getProbeCommand();
    ui->videoInfo->startFrameProbe(frameProbeCommand);
    QString streamProbeCommand = ui->codecTabs->getStreamCommand();
    ui->videoInfo->startStreamProbe(streamProbeCommand);

    ui->videoPlayback->startPlayers();
}
