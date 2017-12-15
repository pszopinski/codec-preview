#ifndef PARAMMANAGER_H
#define PARAMMANAGER_H

#include <QMap>
#include <QString>

class ParameterManager {
  public:
    ParameterManager();
    QString getHint(QString paramName);
    void setHint(QString paramName, QString tooltip);

  private:
    QMap<QString, QString> *paramHints;
    void initTooltips();
};

#endif // PARAMMANAGER_H
