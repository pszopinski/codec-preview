#ifndef H265_H
#define H265_H

#include "codectabs/codectab.h"

#include "constants.h"

class H265 : public Codec
{
public:
    H265();
    void start(QProcess &process, QString file);
};

#endif // H265_H
