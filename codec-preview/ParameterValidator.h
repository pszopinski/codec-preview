#ifndef PARAMSVALIDATOR_H
#define PARAMSVALIDATOR_H

#include <QDebug>
#include <QIntValidator>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QString>

class ParameterValidator {
  public:
    ParameterValidator();
    void addValidation(QLineEdit *&lineEdit, QString parameter);
};

#endif // PARAMSVALIDATOR_H
