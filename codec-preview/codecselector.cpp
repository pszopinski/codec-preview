#include "codecselector.h"
#include "ui_codecselector.h"

CodecSelector::CodecSelector(QWidget *parent)
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
}

bool CodecSelector::canCheck() {
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

CodecSelector::~CodecSelector() { delete ui; }

void CodecSelector::on_MPEG1_clicked() {
    if (selected[2]) {
        selected[2] = !selected[2];
        return;
    }
    if (canCheck()) {
        selected[2] = !selected[2];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[2] = !selected[2];
    }
    lastChecked = 2;
}

void CodecSelector::on_MPEG2_clicked() {
    if (selected[3]) {
        selected[3] = !selected[3];
        return;
    }
    if (canCheck()) {
        selected[3] = !selected[3];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[3] = !selected[3];
    }
    lastChecked = 3;
}

void CodecSelector::on_MJPEG_clicked() {
    if (selected[0]) {
        selected[0] = !selected[0];
        return;
    }
    if (canCheck()) {
        selected[0] = !selected[0];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[0] = !selected[0];
    }
    lastChecked = 0;
}

void CodecSelector::on_H261_clicked() {
    if (selected[1]) {
        selected[1] = !selected[1];
        return;
    }
    if (canCheck()) {
        selected[1] = !selected[1];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[1] = !selected[1];
    }
    lastChecked = 1;
}

void CodecSelector::on_H264_clicked() {
    if (selected[4]) {
        selected[4] = !selected[4];
        return;
    }
    if (canCheck()) {
        selected[4] = !selected[4];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[4] = !selected[4];
    }
    lastChecked = 4;
}

void CodecSelector::on_H265_clicked() {
    if (selected[5]) {
        selected[5] = !selected[5];
        return;
    }
    if (canCheck()) {
        selected[5] = !selected[5];
    } else {
        checkBox[lastChecked]->setChecked(false);
        selected[lastChecked] = !selected[lastChecked];
        selected[5] = !selected[5];
    }
    lastChecked = 5;
}

void CodecSelector::on_buttonBox_accepted() {
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
        // user selected exactly 3 codecs
        hndl->compareWindowStream(indexes[0], indexes[1], indexes[2]);
        close();

    } else {
        // user selected too little codecs
        QMessageBox::information(this, "Codec selection",
                                 "Too little codecs selected!", QMessageBox::Ok,
                                 QMessageBox::Ok);
    }
}

void CodecSelector::setMainWindowHandler(CodecTabsWidget *hndl) {
    this->hndl = hndl;
}

void CodecSelector::on_buttonBox_rejected() { this->close(); }
