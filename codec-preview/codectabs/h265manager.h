#ifndef H265_H
#define H265_H

#include "codecmanager.h"

#include "constants.h"

class H265Manager : public CodecManager
{
public:
    H265Manager();
    void start(QProcess &process, QString file);
};

#endif // H265_H
