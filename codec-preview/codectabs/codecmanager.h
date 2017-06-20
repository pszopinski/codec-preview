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
    CodecTabsWidget *codecTabs;

    QMap<QString, QString> parameters;

  public:
    explicit CodecManager(QWidget *parent = 0);

    QMap<QString, QString> getStreamingParameters();
    void setParameter(QString parameter, QString value);
    QString getParameter(QString parameter);

    virtual void setCodecTabs(CodecTabsWidget *widget);

    // CommonParametersWidget* getCommonParams();

  signals:
    //    void parametersChanged();
  public slots:
};

#endif // CODECMANAGER_H
