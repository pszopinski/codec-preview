#include "h265manager.h"

H265Manager::H265Manager()
{
    encodingParameters = "-c:v libx265 -preset ultrafast -f matroska";
}
