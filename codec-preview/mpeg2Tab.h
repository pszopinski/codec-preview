#ifndef MPEG2_H
#define MPEG2_H

#include "codecTab.h"

class MPEG2 : public Codec
{
public:
    MPEG2();
    void start(QProcess &process);
};

#endif // MPEG2_H
