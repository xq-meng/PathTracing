#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"
#include "ray.h"

class Camera
{
public:
    Camera();

    double width;
    double height;
    double viewAngle;
    double clipPortWidth;
    double clipPortHeight;
    double clipRatio;
    vector3D position;
    vector3D lookAt;
    vector3D up;
    vector3D right;

    void initialize(vector3D camera_position, vector3D camera_lookAt, vector3D camera_up);
    void setViewPort(double camera_width, double camera_height, double camera_viewAngle);
    Ray genRay(int x, int y);
};

#endif // CAMERA_H
