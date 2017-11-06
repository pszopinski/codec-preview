#include "mpeg1.h"

Mpeg1::Mpeg1() {
    addParameter("Bitrate", "b:v", "");
    addParameter("Minrate", "minrate", "");
    addParameter("Maxrate", "maxrate", "");
    addParameter("Aspect ratio", "aspect", "");
    // addParameter("Qscale", "qscale:v", "");
    addParameter("Resolution", "s", "");
}
