#ifndef RAY_H
#define RAY_H

#include "matrix.h"

class Ray
{
public:
    Ray();
    Ray(vector3D ray_origin, vector3D ray_direction);

    vector3D origin;
    vector3D direction;

    void initialize(vector3D ray_origin, vector3D ray_direction);
};

#endif // RAY_H
