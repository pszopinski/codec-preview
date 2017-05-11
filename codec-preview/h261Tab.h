#ifndef H261_H
#define H261_H

#include "codecTab.h"

class H261 : public Codec
{
public:
    H261();
    void start(QProcess &process);
};

#endif // H261_H
