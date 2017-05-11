#ifndef H261_H
#define H261_H

#include "codectab.h"

#include "constants.h"

class H261 : public Codec
{
public:
    H261();
    void start(QProcess &process, QString file);
};

#endif // H261_H
