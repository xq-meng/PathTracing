#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "matrix.h"
#include "ray.h"
#include "ds.h"

class LightSource
{
public:
    LightSource();
    ~LightSource();

    vector3D    center;
    vector3D    emssion;
    double      radius;

    void    setLight(vector3D ls_center, vector3D ls_emssion, double ls_radius);
    Ray     genLightRay(vector3D &point, double &length, double &cosTheta, double &area);
};

#endif // LIGHTSOURCE_H
