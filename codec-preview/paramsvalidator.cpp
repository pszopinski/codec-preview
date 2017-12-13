#include "paramsvalidator.h"

ParamsValidator::ParamsValidator() {}

void ParamsValidator::addValidation(QLineEdit *&lineEdit, QString parameter) {
    if (parameter == "crf") {
        lineEdit->setValidator(new QIntValidator(0, 31));
    }

    if (parameter == "b:v" || parameter == "maxrate" ||
        parameter == "minrate" || parameter == "bufsize") {
        QRegExp REX("[1-9][0-9]*\\.?[0-9]*[kKM]?");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "aspect" || parameter == "s") {
        QRegExp REX("[1-9][0-9]*\\:[1-9][0-9]*");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "s") {
        QRegExp REX("[1-9][0-9]*\\:[1-9][0-9]*");
        lineEdit->setValidator(new QRegExpValidator(REX));
    }

    if (parameter == "r") {
        lineEdit->setValidator(new QIntValidator(0, 1000));
    }

    if (parameter == "qp") {
        lineEdit->setValidator(new QIntValidator(0, 1000));
    }
}
