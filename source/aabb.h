#ifndef AABB_H
#define AABB_H

#include "matrix.h"
#include "ray.h"

class AABB
{
public:
    AABB();
    AABB(vector3D min, vector3D max);

    vector3D bottom_left;
    vector3D top_right;

    void initialize(const vector3D min, const vector3D max);
    void fitVertex(vector3D &vertex);
    bool isHit(Ray& r);
};

#endif // AABB_H
