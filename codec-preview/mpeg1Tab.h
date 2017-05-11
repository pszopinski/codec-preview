#ifndef MPEG1_H
#define MPEG1_H

#include "codecTab.h"

class MPEG1 : public Codec
{
public:
    MPEG1();
    void start(QProcess &process);
};

#endif // MPEG1_H
