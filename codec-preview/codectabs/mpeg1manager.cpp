#include "mpeg1manager.h"

MPEG1Manager::MPEG1Manager() {
    streamingParameters = "-c:v mpeg1video -preset ultrafast -f matroska";
}
