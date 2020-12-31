#ifndef DS_H
#define DS_H

#include <iostream>
#include <string>
#include <vector>
#include <QVector3D>
#include "matrix.h"
#include "aabb.h"
using namespace std;

class Material
{
public:
    Material() {}
    vector3D Kd;
    vector3D Ka;
    vector3D Tf;
    vector3D Ks;
    double Ni;
    double Ns;
};

class Intersection
{
public:
    double      distance;   // the distance of the ray path
    vector3D    normal;
    Material*   matl;
};

class Element
{
public:
    Element();
    ~Element() {}
    Element(vector<vector3D> vertice_position, vector<vector3D> vertice_normal, Material* material);
    void initialize(vector<vector3D> vertice_position, vector<vector3D> vertice_normal, Material* material);

    vector<vector3D>    vertice_position;
    vector<vector3D>    vertice_normal;
    vector3D            origin;
    vector3D            edge1;
    vector3D            edge2;
    Material            *material;
    AABB                box;

    void updateAABBBox();
    bool getIntersection(Ray &r, Intersection &itsn);
};

#endif // DS_H
