#include "allcodecs.h"

AllCodecs::AllCodecs() {
    addParameter("FPS", "r", "30");
    addParameter("Quality", "q:v", "");
    addCheckBox("Motion vectors", "-vf codecview=mv=pf+bf+bb", true);
    addParameter("GOP size", "g", "");
    addParameter("B frames limit", "bf", "");
}
