#ifndef COMMONPARAMETERSWIDGET_H
#define COMMONPARAMETERSWIDGET_H

#include <QWidget>

#include "codectabswidget.h"

namespace Ui {
class CommonParametersWidget;
}

class CommonParametersWidget : public QWidget {
    Q_OBJECT
  private:
    CodecTabsWidget *codecTabs;
    CodecManager *codecManager;

  public:
    explicit CommonParametersWidget(QWidget *parent = 0);
    ~CommonParametersWidget();

    void setCodecTabs(CodecTabsWidget *widget);
    void setCodecManager(CodecManager *widget);
    void retrieveCRF();

  private slots:
    void on_crf_returnPressed();

  private:
    Ui::CommonParametersWidget *ui;
};

#endif // COMMONPARAMETERSWIDGET_H
