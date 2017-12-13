#include "MjpegCodec.h"

MjpegCodec::MjpegCodec() {
    addParameter("Scale", "s", "");
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Aspect ratio", "aspect", "");
    // addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}
