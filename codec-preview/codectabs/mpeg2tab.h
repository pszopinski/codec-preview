#ifndef MPEG2_H
#define MPEG2_H

#include "codectab.h"

#include "constants.h"

class MPEG2 : public Codec
{
public:
    MPEG2();
    void start(QProcess &process, QString file);
};

#endif // MPEG2_H
