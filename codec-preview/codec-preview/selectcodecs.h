#ifndef SELECTCODECS_H
#define SELECTCODECS_H

#include <QDialog>
#include <QCheckBox>
#include "codeccomparisonwindow.h"

namespace Ui {
class SelectCodecs;
}

class SelectCodecs : public QDialog
{
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
    void setMainWindowHandler(CodecComparisonWindow* ccw);


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
    bool bMpeg1 = false;
    bool bMpeg2 = false;
    bool bMjpeg = false;
    bool bH261 = false;
    bool bH264 = false;
    bool bH265 = false;

    QCheckBox c1;
    QCheckBox c2;
    QCheckBox c3;
    QCheckBox c4;
    QCheckBox c5;
    QCheckBox c6;

    int count;


    CodecComparisonWindow* ccw;
};

#endif // SELECTCODECS_H
