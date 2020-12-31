#include "ds.h"

Element::Element(){}

Element::Element(vector<vector3D> vertice_position, vector<vector3D> vertice_normal, Material* material)
{
    initialize(vertice_position, vertice_normal, material);
}

void Element::initialize(vector<vector3D> vertice_position, vector<vector3D> vertice_normal, Material *material)
{
    this->vertice_position = vertice_position;
    this->vertice_normal = vertice_normal;
    this->origin = vertice_position[0];
    this->edge1 = vertice_position[1] - vertice_position[0];
    this->edge2 = vertice_position[2] - vertice_position[0];
    this->material = material;
}

void Element::updateAABBBox()
{
    this->box.initialize(this->vertice_position[0], this->vertice_position[0]);
    for(unsigned int i = 1; i < 3; i++){
        this->box.fitVertex(vertice_position[i]);
    }
    return;
}

bool Element::getIntersection(Ray &r, Intersection &itsn)
{
    double u, v;
    double t_tmp = 0;
    vector3D pVector = crossProduct(r.direction, this->edge2);
    double det = scalarProduct(this->edge1, pVector);
    if(abs(det) < 1e-6)
        return false;
    vector3D tvec = r.origin - this->vertice_position[0];
    u = scalarProduct(tvec, pVector) / det;
    if(u < 0 || u > 1)
        return false;
    vector3D qVector = crossProduct(tvec, this->edge1);
    v = scalarProduct(r.direction, qVector) / det;
    if(v < 0 || u + v > 1)
        return false;
    t_tmp = scalarProduct(this->edge2, qVector) / det;
    if(t_tmp > 0 && t_tmp < 1e+6){
        itsn.distance = t_tmp;
        itsn.normal = (this->vertice_normal[0] + u * (this->vertice_normal[1] - this->vertice_normal[0]) + v * (this->vertice_normal[2] - this->vertice_normal[0])).normalize();
        itsn.matl = this->material;
        return true;
    }
    return false;
}
