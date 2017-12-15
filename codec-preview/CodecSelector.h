#ifndef CODECSELECTOR_H
#define CODECSELECTOR_H

#include <QCheckBox>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>

#include "CodecTabsWidget.h"
#include "CodecComparisonWindow.h"

namespace Ui {
class CodecSelector;
}

class CodecSelector : public QDialog {
    Q_OBJECT

  private:
    Ui::CodecSelector *ui;
    bool selected[6];
    QCheckBox **checkBox;
    int lastChecked;
    CodecComparisonWindow* codecComparisonWindow;

  public:
    explicit CodecSelector(CodecComparisonWindow* codecComparisonWindow, QWidget *parent = 0);
    ~CodecSelector();
    bool getbMpeg1();
    bool getbMpeg2();
    bool getbMjpeg();
    bool getbH261();
    bool getbH264();
    bool getbH265();
    bool canCheck();

  private slots:
    void on_MPEG1_clicked();
    void on_MPEG2_clicked();
    void on_MJPEG_clicked();
    void on_H261_clicked();
    void on_H264_clicked();
    void on_H265_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // CODECSELECTOR_H
