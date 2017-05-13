#include "mjpegmanager.h"

MJPEGManager::MJPEGManager()
{
    encodingParameters = "-c:v libx265 -preset ultrafast -f matroska";
}
