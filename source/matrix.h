#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include <math.h>
#define EPSILON 0.000001
using namespace std;

class Matrix
{
public:
    int                     row;
    int                     col;
    vector<vector<double>>  elem;
};

class vector3D
{
public:
    vector3D();
    vector3D(double x, double y, double z);
    double x();
    double y();
    double z();

    double&     operator [] (int index);
    vector3D    operator +  (vector3D vecToAdd);
    vector3D    operator -  (vector3D vecToMin);
    vector3D    operator *  (double scale);
    vector3D    operator /  (double divis);
    vector3D    operator *  (vector3D vecToMul);

    double      module();
    vector3D    normalize();

    friend vector3D operator * (double scale, vector3D v);
    friend vector3D operator - (vector3D v);

private:
    double data[3];
};

vector3D    crossProduct(vector3D v1, vector3D v2);
double      scalarProduct(vector3D v1, vector3D v2);
double      cosVectorialAngle(vector3D v1, vector3D v2);

#endif // Matrix_H
