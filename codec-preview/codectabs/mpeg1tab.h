#ifndef MPEG1_H
#define MPEG1_H

#include "codectab.h"

#include "constants.h"

class MPEG1 : public Codec
{
public:
    MPEG1();
    void start(QProcess &process, QString file);
};

#endif // MPEG1_H
