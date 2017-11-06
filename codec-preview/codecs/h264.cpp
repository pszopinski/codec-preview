#include "h264.h"

H264::H264() {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Costant Rate Factor", "crf", "");
    addParameter("Resolution", "s", "");
}
