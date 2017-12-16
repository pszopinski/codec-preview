#include "Mpeg1Codec.h"

Mpeg1Codec::Mpeg1Codec() {
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", false);
    addParameter("GOP size", "g", "");
    addParameter("B frames limit", "bf", "");
}
