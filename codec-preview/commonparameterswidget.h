#ifndef COMMONPARAMETERSWIDGET_H
#define COMMONPARAMETERSWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "codectabswidget.h"

namespace Ui {
class CommonParametersWidget;
}

class CommonParametersWidget : public QWidget {
    Q_OBJECT
  private:
    CodecTabsWidget *codecTabs;
    CodecManager *codecManager;
    QMap<QString, QLineEdit*> parameterFields;



  public:
    explicit CommonParametersWidget(QWidget *parent = 0);
    ~CommonParametersWidget();

    void setCodecTabs(CodecTabsWidget *widget);
    void setCodecManager(CodecManager *widget);
    void retrieveParameter(QString parameter);

    void setField(QString parameter);




  private slots:
    void retrieveAllParameters();

    void on_crf_returnPressed();

    void on_frameRate_returnPressed();

    void on_scale_returnPressed();

private:
    Ui::CommonParametersWidget *ui;
};

#endif // COMMONPARAMETERSWIDGET_H
