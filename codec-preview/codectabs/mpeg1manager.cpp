#include "mpeg1manager.h"

MPEG1Manager::MPEG1Manager()
{
    encodingParameters = "-c:v mpeg1video -preset ultrafast -f matroska";
}
