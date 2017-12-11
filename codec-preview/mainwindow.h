#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>
#include <QInputDialog>

//#include "codecselector.h"
#include "ffmpegcommand.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
  private:
    Ui::MainWindow *ui;
  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);
    void stream();
    void resetPlayback();

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
};



#endif // CODECCOMPARISONWINDOW_H
