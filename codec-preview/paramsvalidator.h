#ifndef PARAMSVALIDATOR_H
#define PARAMSVALIDATOR_H

#include <QDebug>
#include <QIntValidator>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QString>

class ParamsValidator {
  public:
    ParamsValidator();
    void addValidation(QLineEdit *&lineEdit, QString parameter);
};

#endif // PARAMSVALIDATOR_H
