#include "AnyCodec.h"

AnyCodec::AnyCodec() {
    addParameter("FPS", "r", "");
    addParameter("Quantization", "qscale:v", "");
}
