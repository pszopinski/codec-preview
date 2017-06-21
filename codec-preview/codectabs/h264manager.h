#ifndef H264MANAGER_H
#define H264MANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class H264Manager;
}

class H264Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H264Manager(QWidget *parent = 0);
    ~H264Manager();

    void setCodecTabs(CodecTabsWidget *widget);
    // CommonParametersWidget* getCommonParams();
private slots:
    void on_crf_returnPressed();

private:
    Ui::H264Manager *ui;
};

#endif // H264MANAGER_H
