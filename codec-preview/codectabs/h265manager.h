#ifndef H265MANAGER_H
#define H265MANAGER_H

#include <QWidget>

#include "codecmanager.h"

namespace Ui {
class H265Manager;
}

class H265Manager : public CodecManager {
    Q_OBJECT

  public:
    explicit H265Manager(QWidget *parent = 0);
    ~H265Manager();

    void setCodecTabs(CodecTabsWidget *widget);
    // CommonParametersWidget* getCommonParams();
private slots:
    void on_crf_returnPressed();

private:
    Ui::H265Manager *ui;
};

#endif // H265MANAGER_H
