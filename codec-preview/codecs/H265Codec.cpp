#include "H265Codec.h"

H265Codec::H265Codec() {
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", false);
    addParameter("GOP size", "g", "", "50");
    addParameter("B frames limit", "bf", "", "50");
}
