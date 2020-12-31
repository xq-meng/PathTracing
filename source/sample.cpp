#include "sample.h"

Ray Sample::diffuseReflectionSample(vector3D position, vector3D normal, double &pdf)
{
    const double PI = acos(-1);
    vector3D up = normal;
    vector3D front;
    if(abs(up[0]) < 1e-6)
        front = crossProduct(vector3D(1, 0, 0), up).normalize();
    else
        front = crossProduct(vector3D(0, 1, 0), up).normalize();
    vector3D right = crossProduct(front, up).normalize();
    double rHat = sqrt(double(rand()) / double(RAND_MAX));
    double thetaHat = 2 * PI * double(rand()) / double(RAND_MAX);
    double u = rHat * cos(thetaHat);
    double v = rHat * sin(thetaHat);
    double w = 1.0 - u * u - v * v;
    w = (w > 0) ? sqrt(w) : 0;
    pdf = w / PI;
    vector3D direction = u * right + v * front + w * up;    // ensures direction.module = 1
    return Ray(position, direction);
}

Ray Sample::specularReflectionSample(vector3D position, vector3D normal, vector3D incRay, double ns, double &pdf)
{
    const double PI = acos(-1);
    vector3D up = (incRay + 2 * abs(scalarProduct(normal, incRay)) * normal).normalize();
    vector3D front;
    if(abs(up[0]) < 1e-6)
        front = crossProduct(vector3D(1, 0, 0), up).normalize();
    else
        front = crossProduct(vector3D(0, 1, 0), up).normalize();
    vector3D right = crossProduct(front, up).normalize();
    double thetaHat = acos(pow(double(rand()) / double(RAND_MAX), 1.0 / double(ns + 1)));
    double alphaHat = 2 * PI * double(rand()) / double(RAND_MAX);
    double u = cos(alphaHat) * sin(thetaHat);
    double v = sin(alphaHat) * sin(thetaHat);
    double w = cos(thetaHat);
    pdf = (ns + 1) / (2 * PI) * pow(w, ns);
    vector3D direction = u * right + v * front + w * up;
    if(scalarProduct(direction, normal) < 0)
        direction = (-1) * u * right + (-1) * v *front + w * up;
    direction = direction.normalize();
    return Ray(position, direction);
}
