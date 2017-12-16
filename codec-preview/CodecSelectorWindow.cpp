#include "CodecSelectorWindow.h"
#include "ui_codecselector.h"

CodecSelectorWindow::CodecSelectorWindow(CodecComparisonWindow *codecComparisonWindow, QWidget *parent)
    : QDialog(parent), ui(new Ui::CodecSelector) {
    ui->setupUi(this);
    checkBox = new QCheckBox *[6];
    checkBox[0] = ui->MJPEG;
    checkBox[1] = ui->H261;
    checkBox[2] = ui->MPEG1;
    checkBox[3] = ui->MPEG2;
    checkBox[4] = ui->H264;
    checkBox[5] = ui->H265;
    for (int i = 0; i < 6; i++)
        selected[i] = false;

    this->codecComparisonWindow = codecComparisonWindow;
}

bool CodecSelectorWindow::canCheck() {
    int count = 0;
    for (int i = 0; i < 6; i++) {
        if (selected[i])
            ++count;
    }
    if (count > 2)
        return false;
    else
        return true;
}

void CodecSelectorWindow::onCodecClicked(int i) {
    if (selected[i]) {
        selected[i] = !selected[i];
        return;
    }
    if (canCheck()) {
        selected[i] = !selected[i];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[i] = !selected[i];
    }
    lastChecked = i;
}

CodecSelectorWindow::~CodecSelectorWindow() { delete ui; }

void CodecSelectorWindow::on_MPEG1_clicked() { onCodecClicked(2); }

void CodecSelectorWindow::on_MPEG2_clicked() { onCodecClicked(3); }

void CodecSelectorWindow::on_MJPEG_clicked() { onCodecClicked(0); }

void CodecSelectorWindow::on_H261_clicked() { onCodecClicked(1); }

void CodecSelectorWindow::on_H264_clicked() { onCodecClicked(4); }

void CodecSelectorWindow::on_H265_clicked() { onCodecClicked(5); }

void CodecSelectorWindow::on_buttonBox_accepted() {
    int indexes[3];
    int n = 0;
    // locate selected codec indexes
    for (int i = 0; i < 6; i++) {
        if (selected[i]) {
            indexes[n] = i;
            n++;
        }
    }
    if (n == 3) {
        close();
        // user selected exactly 3 codecs
        codecComparisonWindow->compareWindowStream(indexes[0], indexes[1], indexes[2]);

    } else {
        // user selected too little codecs
        QMessageBox::information(this, "Codec selection", "Too little codecs selected!", QMessageBox::Ok,
                                 QMessageBox::Ok);
    }
}

void CodecSelectorWindow::on_buttonBox_rejected() { this->close(); }
