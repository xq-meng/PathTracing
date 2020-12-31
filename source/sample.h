#ifndef SAMPLE_H
#define SAMPLE_H

#include "matrix.h"
#include "ray.h"

namespace Sample
{
    Ray diffuseReflectionSample(vector3D position, vector3D normal, double &pdf);
    Ray specularReflectionSample(vector3D position, vector3D normal, vector3D incRay, double ns, double &pdf);
};

#endif // SAMPLE_H
