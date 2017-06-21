#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QDebug>
#include <QMap>
#include <QWidget>
#include <QLineEdit>


//#include "commonparameterswidget.h"


#include "codectabswidget.h"


class CodecManager : public QWidget {
    Q_OBJECT
    CodecTabsWidget* codecTabs;

  protected:
    QMap<QString, QString> parameters;

    QMap<QString, QLineEdit*> parameterFields;



  public:
    explicit CodecManager(QWidget *parent = 0);

    QMap<QString, QString> getStreamingParameters();
    void setParameter(QString parameter, QString value);
    QString getParameter(QString parameter);

    void setField(QString parameter);

    virtual void setCodecTabs(CodecTabsWidget *widget);


    // CommonParametersWidget* getCommonParams();

  signals:
    //    void parametersChanged();
  public slots:
};

#endif // CODECMANAGER_H
