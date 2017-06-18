#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QDebug>
#include <QMap>
#include <QWidget>

//#include "codectabswidget.h"

//#include "commonparameterswidget.h"

class CodecTabsWidget;

class CodecManager : public QWidget {
    Q_OBJECT

  protected:
    QString encoderParameter;
    QString pixelFormatParameter;
    QString crfParameter;
    QString filterParameter;
    QString presetParameter;
    QString formatParameter;
    CodecTabsWidget *codecTabs;

  public:
    explicit CodecManager(QWidget *parent = 0);

    QMap<QString, QString> getStreamingParameters();
    void setCRF(QString value);
    QString getCRF();

    virtual void setCodecTabs(CodecTabsWidget *widget);

    // CommonParametersWidget* getCommonParams();

  signals:
    //    void parametersChanged();
  public slots:
};

#endif // CODECMANAGER_H
