#include "Main.h"

Collider::Collider(float centerX, float centerY, float width, float height, float angle){

        center = new Vector2D(centerX, centerY);
        angle = angle/180 * M_PI;
        Vector2D p1;
        p1.x = centerX + (width/2  * cos(angle)) - (height/2  * sin(angle));
        p1.y = centerY + (width/2 * sin(angle)) + (height/2 * cos(angle));
        points.push_back(p1);
        Vector2D p2;
        p2.x = centerX + (-width/2  * cos(angle)) - (height/2  * sin(angle));
        p2.y = centerY + (-width/2 * sin(angle)) + (height/2 * cos(angle));
        points.push_back(p2);
        Vector2D p3;
        p3.x = centerX + (-width/2  * cos(angle)) - (-height/2  * sin(angle));
        p3.y = centerY + (-width/2 * sin(angle)) + (-height/2 * cos(angle));
        points.push_back(p3);
        Vector2D p4;
        p4.x = centerX + (width/2  * cos(angle)) - (-height/2  * sin(angle));
        p4.y = centerY + (width/2 * sin(angle)) + (-height/2 * cos(angle));
        points.push_back(p4);

}

void Collider::update(float centerX, float centerY, float width, float height, float angle){

        center->x = centerX;
        center->y = centerY;
        angle = angle/180 * M_PI;
        points[0].x = centerX + (width/2  * cos(angle)) - (height/2  * sin(angle));
        points[0].y = centerY + (width/2 * sin(angle)) + (height/2 * cos(angle));

        points[1].x = centerX + (-width/2  * cos(angle)) - (height/2  * sin(angle));
        points[1].y = centerY + (-width/2 * sin(angle)) + (height/2 * cos(angle));

        points[2].x = centerX + (-width/2  * cos(angle)) - (-height/2  * sin(angle));
        points[2].y = centerY + (-width/2 * sin(angle)) + (-height/2 * cos(angle));

        points[3].x = centerX + (width/2  * cos(angle)) - (-height/2  * sin(angle));
        points[3].y = centerY + (width/2 * sin(angle)) + (-height/2 * cos(angle));

}

Vector2D Collider::areColliding(Collider * col1, Collider * col2)
{
    float overlap = 100000;
    Vector2D smallest(0,0);
    Vector2D * axes1 = getAxes(col1);
    Vector2D * axes2 = getAxes(col2);

    for (int i = 0; i < col1->points.size(); i++)
    {
        Projection * p1 = col2->project(axes1[i]);
        Projection * p2 = col1->project(axes1[i]);

        if (Projection::overlap(p1,p2)){
            delete_object(p1);
            delete_object(p2);
            delete_object(axes1);
            delete_object(axes2);
            return {0,0};
        }
        else {
            if (Projection::getOverlap(p1,p2) < overlap){
                overlap = Projection::getOverlap(p1,p2);
                smallest = axes1[i];
            }
        }

        delete_object(p1);
        delete_object(p2);


    }

    for (int i = 0; i < col2->points.size(); i++)
    {
        Projection * p1 = col2->project(axes2[i]);
        Projection * p2 = col1->project(axes2[i]);

        if (Projection::overlap(p1,p2)){
            delete_object(p1);
            delete_object(p2);
            delete_object(axes1);
            delete_object(axes2);
            return {0,0};
        }
        else {
            if (Projection::getOverlap(p1,p2) < overlap){
                overlap = Projection::getOverlap(p1,p2);
                smallest = axes2[i];
            }
        }

        delete_object(p1);
        delete_object(p2);
    }

    delete_object(axes1);
    delete_object(axes2);

    Vector2D ba(col1->center->x-col2->center->x, col1->center->y-col2->center->y);
    if(smallest.Dot(ba) < 0.0){
        smallest.x*=-1;
        smallest.y*=-1;
    }
    smallest = (smallest*overlap).Normalize();
    std::cout << overlap << std::endl;
    return smallest;
}

Projection * Collider::project (Vector2D axis)
{
    float min = axis.Dot(this->points[0]);
    float max = min;

    for (int i = 1; i < points.size(); i++) {
      float p = axis.Dot(points[i]);
      if (p < min) {
        min = p;
      } else if (p > max) {
        max = p;
      }
    }

    auto * proj = new Projection(min, max);

    return proj;
}

Vector2D * Collider::getAxes(Collider * col){

    Vector2D * axes = nullptr;
    axes = new Vector2D[col->points.size()];
    for (int i = 0; i < col->points.size(); i++)
    {
        Vector2D p1 = col->points[i];
        Vector2D p2 = col->points[i + 1 == col->points.size() ? 0 : i + 1];
        Vector2D edge = p1.Subtract(p2);
        Vector2D normal = edge.Perp();
        axes[i] = normal;
    }
    return axes;
}
