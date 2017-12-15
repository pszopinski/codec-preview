#include "MjpegCodec.h"

MjpegCodec::MjpegCodec() {
    addParameter("Scale", "s", "");
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Buffer size", "bufsize", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Resolution", "s", "");
}
