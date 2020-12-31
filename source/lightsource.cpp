#include "lightsource.h"

LightSource::LightSource()
{

}

LightSource::~LightSource()
{

}

void LightSource::setLight(vector3D ls_center, vector3D ls_emssion, double ls_radius)
{
    this->center = ls_center;
    this->emssion = ls_emssion;
    this->radius = ls_radius;
}

Ray LightSource::genLightRay(vector3D &point, double &length, double &cosTheta, double &area)
{
    const double PI = acos(-1);
    vector3D dw = (point - this->center).normalize();
    vector3D du = crossProduct(dw, vector3D(1, 0, 0));
    if(du.module() < 1e-6)
        du = crossProduct(dw, vector3D(0, 1, 0)).normalize();
    else
        du = du.normalize();
    vector3D dv = crossProduct(du, dw).normalize();
    double distance = (this->center - point).module();
    if(distance < this->radius){
        area = 0;
        return Ray();
    }
    double cosTheta0 = this->radius / distance;
    double sphereHap = this->radius * (1 - cosTheta0);
    area = 2 * PI * this->radius * sphereHap;
    double r1 = double(rand()) / double(RAND_MAX);
    double r2 = double(rand()) / double(RAND_MAX);
    double sampleTheta = r1 * acos(cosTheta0);
    double sampleAlpha = 2 * PI *r2;
    vector3D sampleDirection = sin(sampleTheta) * cos(sampleAlpha) * du + sin(sampleTheta) * sin(sampleAlpha) * dv + cos(sampleTheta) * dw; // sampleDirection.module = 1
    vector3D samplePosition = this->center + sampleDirection * this->radius;
    vector3D lightDirection = samplePosition - point;
    length = lightDirection.module();
    lightDirection = lightDirection.normalize();
    cosTheta = scalarProduct(-lightDirection, sampleDirection);
    cosTheta = (cosTheta > 0) ? cosTheta : 0;
    Ray lightRay(point, lightDirection);
    return lightRay;
}
