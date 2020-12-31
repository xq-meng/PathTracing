#include "ray.h"

Ray::Ray()
{

}

Ray::Ray(vector3D ray_origin, vector3D ray_direction)
{
    this->initialize(ray_origin, ray_direction);
}

void Ray::initialize(vector3D ray_origin, vector3D ray_direction)
{
    this->origin = ray_origin;
    this->direction = ray_direction;
}
