#include "codecpreview.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CodecPreview w;
    w.show();

    return a.exec();
}
