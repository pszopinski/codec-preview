#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QInputDialog>
#include <QMainWindow>
#include <QTabWidget>

//#include "codecselector.h"
#include "CodecComparisonWindow.h"
#include "CodecParametersWidget.h"
#include "FFmpegCommand.h"
#include "MacroblockPickerView.h"
#include "StreamingProcess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
  private:
    Ui::MainWindow *ui;
    QVector<CodecParametersWidget *> codecWidgets;
    StreamingProcess *streamingProcess;
    QProcess cameraNameGetterProcess;
    CodecComparisonWindow *codecComparisonWindow;
    QProcess singleFrameProcess;
    QGraphicsScene *scene;
    MacroblockPickerView *view;
    QGraphicsPixmapItem *item;
    QPixmap *pixmap;

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    void stream();
    void resetPlayback();
    void openFromFile(QString filePath);
    void openFromCamera();
    QString getStreamingParameters();
    void getSingleFrame();

  signals:
    void settingsChanged();

  private slots:
    void on_actionOpen_file_triggered();
    void on_actionOpen_from_camera_triggered();
    void on_actionCompare_multiple_codecs_triggered();
    void on_actionChange_raw_host_triggered();
    void on_actionChange_raw_port_triggered();
    void on_actionChange_encoded_host_triggered();
    void on_actionChange_encoded_port_triggered();

    void on_actionHelp_triggered();
    void on_actionMacroblocks_triggered();

    void parseCameraNameProbeOutput(int a, QProcess::ExitStatus b);

    void onSingleFrameGotten(int a, QProcess::ExitStatus b);

    void on_actionOriginal_size_toggled(bool arg1);
};

#endif // CODECCOMPARISONWINDOW_H
