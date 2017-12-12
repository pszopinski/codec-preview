#ifndef CODEC_H
#define CODEC_H

#include <QList>
#include <qt-ordered-map/orderedmap.h>

class Codec {
  public:
    Codec();

  protected:
    OrderedMap<QString, OrderedMap<QString, QString>> *parameters =
        new OrderedMap<QString, OrderedMap<QString, QString>>();
    OrderedMap<QString, OrderedMap<QString, QString>> *comboBoxes =
        new OrderedMap<QString, OrderedMap<QString, QString>>();
    OrderedMap<QString, OrderedMap<QString, QString>> *checkBoxes =
        new OrderedMap<QString, OrderedMap<QString, QString>>();
    OrderedMap<QString, OrderedMap<QString, QString>> *stats =
        new OrderedMap<QString, OrderedMap<QString, QString>>();

    void addParameter(QString paramName, QString paramValue,
                      QString paramDefault);
    void addComboBox(QString paramName, QString paramValue,
                     OrderedMap<QString, QString> paramMap);
    void addCheckBox(QString paramName, QString command, bool state);
    void addStat();

  public:
    OrderedMap<QString, QString> getParameter(QString paramName);
    OrderedMap<QString, QString> getComboBox(QString paramName);
    OrderedMap<QString, QString> getCheckBox(QString paramName);
    QList<QString> getParameterKeys();
    QList<QString> getComboBoxKeys();
    QList<QString> getCheckBoxKeys();
};

#endif // CODEC_H
