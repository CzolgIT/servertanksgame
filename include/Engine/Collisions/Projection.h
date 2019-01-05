#include "Main.h"

class Projection {
public:
    float min, max;

    Projection(float min, float max);

    static bool overlap(Projection * p1, Projection * p2);

    static float getOverlap(Projection * p1, Projection * p2);

};
