#include "allcodecs.h"

AllCodecs::AllCodecs() {
    addParameter("FPS", "r", "");
    addParameter("Quantization", "qp", "");
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", true);
}
