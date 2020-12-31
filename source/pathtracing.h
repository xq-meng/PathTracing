#ifndef PATHTRACING_H
#define PATHTRACING_H

#include "frame.h"
#include "camera.h"
#include "ray.h"

class PathTracing
{
public:
    PathTracing();
    ~PathTracing();

    int                         numRayinPixel;
    int                         numSmpinLight;
    int                         maxDepth = 5;
    Frame*                      frame;
    Camera*                     camera;
    vector3D                    ambientLight;
    vector<vector<vector3D>>    image;

    vector3D    illuminate(Ray &r, Intersection &itsn);
    vector3D    rayTracing(Ray &r, int depth);
    void        render();

};

#endif // PATHTRACING_H
