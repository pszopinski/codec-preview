#include "codec.h"

Codec::Codec()
{

}

void Codec::addStat()
{

}

void Codec::addParameter(QString paramName, QString paramValue, QString paramDefault)
{
    QMap<QString, QString> param;
    param.insert("value", paramValue);
    param.insert("default", paramDefault);
    parameters->insert(paramName, param);
}

void Codec::addCombo(QString paramName, QString paramValue, QMap<QString, QString> paramMap)
{
    QMap<QString, QString> comboCopy = QMap<QString, QString>(paramMap);
    comboCopy.insert("value", paramValue);
    comboBoxes->insert(paramName, comboCopy);
}

QMap<QString, QString> Codec::getParameter(QString paramName)
{
    return parameters->value(paramName);
}

QMap<QString, QString> Codec::getCombo(QString paramName)
{
    return comboBoxes->value(paramName);
}


QList<QString> Codec::getParamKeys()
{
    QList<QString> keys;
    for( auto key: parameters->keys() )
    {
        keys.append(key);
    }
    return keys;
}

QList<QString> Codec::getComboKeys()
{
    QList<QString> keys;
    for( auto key: comboBoxes->keys() )
    {
        keys.append(key);
    }
    return keys;
}

