#include "aabb.h"

AABB::AABB()
{

}

AABB::AABB(vector3D min, vector3D max)
{
    this->initialize(min, max);
}

void AABB::initialize(const vector3D min, const vector3D max)
{
    this->bottom_left = min;
    this->top_right = max;
}

bool AABB::isHit(Ray& ray)
{
    // linear equation of ray: ray(t) = ray.origin + t * ray.direction
    double t_near = 0;
    double t_far = 999999;
    for(int i = 0; i < 3; i++){
        if(abs(ray.direction[i]) < 1e-10)
            if(ray.origin[i] < this->bottom_left[i] || ray.origin[i] > this->top_right[i])
                return false;
        double t1 = (this->bottom_left[i] - ray.origin[i]) / ray.direction[i];
        double t2 = (this->top_right[i] - ray.origin[i]) / ray.direction[i];
        double tmin = (t1 < t2) ? t1 : t2;
        double tmax = (t1 < t2) ? t2 : t1;
        t_near = (t_near < tmin) ? tmin : t_near;
        t_far = (t_far > tmax) ? tmax : t_far;
        if(t_far < t_near || t_far < 0)
            return false;
    }
    return true;
}

void AABB::fitVertex(vector3D &vertex)
{
    for(int i = 0; i < 3; i++){
        if(this->bottom_left[i] > vertex[i])
            this->bottom_left[i] = vertex[i];
        if(this->top_right[i] < vertex[i])
            this->top_right[i] = vertex[i];
    }
}
