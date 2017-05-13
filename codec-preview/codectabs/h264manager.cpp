#include "h264manager.h"

H264Manager::H264Manager() {
    streamingParameters = "-c:v libx264 -preset ultrafast -f matroska";
}
