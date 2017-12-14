#include "AnyCodec.h"

AnyCodec::AnyCodec() {
    addParameter("FPS", "r", "30");
    addParameter("Quantization", "qp", "");
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", true);
    addParameter("Qscale", "qscale:v", "");
}
