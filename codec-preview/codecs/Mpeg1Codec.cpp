#include "Mpeg1Codec.h"

Mpeg1Codec::Mpeg1Codec() {
    addSlider("Quantization", "q:v", "24", "1", "51");
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", false);
    addParameter("GOP size", "g", "", "50");
    addParameter("B frames limit", "bf", "", "50");
}
