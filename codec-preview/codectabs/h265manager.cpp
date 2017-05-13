#include "h265manager.h"

H265Manager::H265Manager() {
    streamingParameters = "-c:v libx265 -preset ultrafast -f matroska";
}
