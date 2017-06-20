#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileDialog>
#include <QMainWindow>

#include "selectcodecs.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
  public:
    Ui::MainWindow *ui;

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

    void broadcast();

  private slots:
    void on_actionOpen_file_triggered();

    void on_actionOpen_from_camera_triggered();

    void on_actionCompare_multiple_codecs_triggered();

  signals:
    void settingsChanged();
};

#endif // CODECCOMPARISONWINDOW_H
