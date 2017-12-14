#include "MjpegCodec.h"

MjpegCodec::MjpegCodec() {
    addParameter("Scale", "s", "");
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Aspect ratio", "aspect", "");
    addParameter("Resolution", "s", "");
}
