#ifndef H265_H
#define H265_H

#include "codecTab.h"

class H265 : public Codec
{
public:
    H265();
    void start(QProcess &process);
};

#endif // H265_H
