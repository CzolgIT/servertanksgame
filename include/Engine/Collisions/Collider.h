#ifndef Collider_h
#define Collider_h

#include "Main.h"

class Collider {

public:
    Collider(float centerX, float centerY, float width, float height, float angle = 0);
    explicit Collider(Vector2D * points)
    {
    }

    void update(float centerX, float centerY, float width, float height, float angle = 0);

    static Vector2D areColliding(Collider * col1, Collider * col2);

    Projection * project (Vector2D axis);

    Vector2D * center;

    static Vector2D * getAxes(Collider * col);

    std::vector<Vector2D> points;

};
#endif /* Collider_h */
