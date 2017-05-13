#include "h264manager.h"

H264Manager::H264Manager()
{
    encodingParameters = "-c:v libx264 -preset ultrafast -f matroska";
}
