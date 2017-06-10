#ifndef SELECTCODECS_H
#define SELECTCODECS_H

#include "codeccomparisonwindow.h"
#include <QCheckBox>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class SelectCodecs;
}

class SelectCodecs : public QDialog {
    Q_OBJECT

  public:
    explicit SelectCodecs(QWidget *parent = 0);
    ~SelectCodecs();

    bool getbMpeg1();
    bool getbMpeg2();
    bool getbMjpeg();
    bool getbH261();
    bool getbH264();
    bool getbH265();
    bool canCheck();
    void setMainWindowHandler(CodecComparisonWindow *ccw);

  private slots:
    void on_MPEG1_clicked();

    void on_MPEG2_clicked();

    void on_MJPEG_clicked();

    void on_H261_clicked();

    void on_H264_clicked();

    void on_H265_clicked();

    void on_buttonBox_accepted();

  private:
    Ui::SelectCodecs *ui;
    bool selected[6];
    QCheckBox **checkBox;
    int lastChecked;

    CodecComparisonWindow *ccw;
};

#endif // SELECTCODECS_H
