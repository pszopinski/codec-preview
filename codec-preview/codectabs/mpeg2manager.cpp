#include "mpeg2manager.h"

MPEG2Manager::MPEG2Manager()
{
    encodingParameters = "-c:v mpeg2video -preset ultrafast -f matroska";
}
