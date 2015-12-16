#include "GBBase.h"

void GBColor::defineColorInt(){
    colorint = (newC.r << 10) | (newC.g << 5) | newC.b;
    return;
}