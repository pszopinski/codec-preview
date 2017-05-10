#ifndef AVC_H
#define AVC_H

#include "codec.h"

class AVC : public Codec
{
public:
    AVC();
    void start(QProcess &process);
};

#endif // AVC_H
