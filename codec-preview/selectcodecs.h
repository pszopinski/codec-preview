#ifndef SELECTCODECS_H
#define SELECTCODECS_H

#include <QCheckBox>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>

#include "codectabswidget.h"

namespace Ui {
class SelectCodecs;
}

class SelectCodecs : public QDialog {
    Q_OBJECT

  private:
    Ui::SelectCodecs *ui;
    bool selected[6];
    QCheckBox **checkBox;
    int lastChecked;
    CodecTabsWidget *hndl;

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
    void setMainWindowHandler(CodecTabsWidget *hndl);

  private slots:
    void on_MPEG1_clicked();
    void on_MPEG2_clicked();
    void on_MJPEG_clicked();
    void on_H261_clicked();
    void on_H264_clicked();
    void on_H265_clicked();
    void on_buttonBox_accepted();
};

#endif // SELECTCODECS_H
