#include "Main.h"

Projection::Projection(float min, float max)
{
    this->min = min;
    this->max = max;
}

bool Projection::overlap(Projection * p1, Projection * p2)
{
    return p2->min >= p1->max || p1->min >= p2->max;
}

float Projection::getOverlap(Projection * p1, Projection * p2)
{
    return (p1->max < p2->max) ? p1->max - p2->min : p2->max - p1->min;
}
