#ifndef CODEC_H
#define CODEC_H

#include <QMap>
#include <QList>


class Codec
{
public:
    Codec();

protected:
    QMap<QString, QMap<QString, QString>> *parameters = new QMap<QString, QMap<QString, QString>>();
    QMap<QString, QMap<QString, QString>> *comboBoxes = new QMap<QString, QMap<QString, QString>>();
    QMap<QString, QMap<QString, QString>> *stats = new QMap<QString, QMap<QString, QString>>();

    void addStat();
    void addParameter(QString paramName, QString paramValue, QString paramDefault);
    void addCombo(QString paramName, QString paramValue, QMap<QString, QString> paramMap);
public:
    QMap<QString, QString> getParameter(QString paramName);
    QMap<QString, QString> getCombo(QString paramName);
    QList<QString> getParamKeys();
    QList<QString> getComboKeys();




};

#endif // CODEC_H
