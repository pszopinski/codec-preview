#include "Mpeg1Codec.h"

Mpeg1Codec::Mpeg1Codec() {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    // addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}
