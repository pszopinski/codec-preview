#include "mjpegmanager.h"

MJPEGManager::MJPEGManager() {
    streamingParameters = "-c:v libx265 -preset ultrafast -f matroska";
}
