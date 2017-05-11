#ifndef H261_H
#define H261_H

#include "codecmanager.h"

#include "constants.h"

class H261Manager : public CodecManager
{
public:
    H261Manager();
    void start(QProcess &process, QString file);
};

#endif // H261_H
