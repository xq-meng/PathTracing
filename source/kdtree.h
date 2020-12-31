#ifndef KDTREE_H
#define KDTREE_H

#include "ds.h"
#include "aabb.h"
#include "ray.h"

class KDTreeNode
{
public:
    KDTreeNode();

    KDTreeNode*         left;
    KDTreeNode*         right;
    vector<Element*>    elems;
    AABB                box;

    bool                isLeaf;
    int                 splitAxis;  // 0 for x, 1 for y, 2 for z
    int                 elemNum;

    void build(vector<Element*> &elementList, AABB &ogBox, int depth);
    bool intersect(Ray &r, Intersection &itsn);
    bool isShield(Ray &r, double length);
};

#endif // KDTREE_H
