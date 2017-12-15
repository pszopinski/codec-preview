#include "ParameterValidator.h"

ParameterValidator::ParameterValidator() {}

void ParameterValidator::addValidation(QLineEdit *&lineEdit, QString parameter) {
    if (parameter == "crf") {
        // lineEdit->setValidator(new QIntValidator(0, 31));
        QRegExp REX("([0-9]|[1-2][0-9]|[3][0-1])");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "b:v" || parameter == "maxrate" || parameter == "minrate" || parameter == "bufsize") {
        QRegExp REX("[0-9]*\\.?[0-9]*[kKM]?");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "aspect" || parameter == "s") {
        QRegExp REX("[0-9]*\\:[0-9]*");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "s") {
        QRegExp REX("[0-9]*\\:[1-9][0-9]*");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "r") {
        //        lineEdit->setValidator(new QIntValidator(0, 1000));
        QRegExp REX("([0-9]|[1-9][0-9]|[1-9][0-9][0-9])?"); // 0-999
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "qp") {
        //        lineEdit->setValidator(new QIntValidator(0, 1000));
        QRegExp REX("([0-9]|[1-9][0-9]|[1-9][0-9][0-9])?"); // 0-999
        lineEdit->setValidator(new QRegExpValidator(REX));
    }
}
