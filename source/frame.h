#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "ds.h"
#include "matrix.h"
#include "ray.h"
#include "kdtree.h"
#include "lightsource.h"
using namespace std;

class Frame
{
public:
    Frame(){}
    ~Frame(){}

    vector<Element*>        elems;
    map<string, Material>   matlList;
    vector<LightSource*>    lights;
    KDTreeNode              kdTree;
    AABB                    boundingBox;

    bool load_obj(string objfilename);
    bool load_mtl(string mtlfilename);
    void updateBox();
    void buildKDtree();
    bool intersect(Ray itRay, Intersection &itsn);
    bool isShield(Ray r, double length);
};

#endif // FRAME_H
