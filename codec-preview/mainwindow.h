#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

//#include "codecselector.h"

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
};



#endif // CODECCOMPARISONWINDOW_H
