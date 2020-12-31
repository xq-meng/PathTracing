#include "matrix.h"

vector3D::vector3D()
{
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
}

vector3D::vector3D(double x, double y, double z)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

double vector3D::x()
{
    return data[0];
}

double vector3D::y()
{
    return data[1];
}

double vector3D::z()
{
    return data[2];
}

double& vector3D::operator[](int index)
{
    return data[index];
}

vector3D vector3D::operator+(vector3D vecToAdd)
{
    vector3D result(this->x() + vecToAdd.x(), this->y() + vecToAdd.y(), this->z() + vecToAdd.z());
    return result;
}

vector3D vector3D::operator-(vector3D vecToMin)
{
    vector3D result(this->x() - vecToMin.x(), this->y() - vecToMin.y(), this->z() - vecToMin.z());
    return result;
}

vector3D vector3D::operator*(double scale)
{
    vector3D result(this->x() * scale, this->y() * scale, this->z() * scale);
    return result;
}

vector3D vector3D::operator/(double divis)
{
    vector3D result(this->x() / divis, this->y() / divis, this->z() / divis);
    return result;
}

vector3D vector3D::operator*(vector3D vecToMul)
{
    vector3D result(this->x() * vecToMul.x(), this->y() * vecToMul.y(), this->z() * vecToMul.z());
    return result;
}

double vector3D::module()
{
    return sqrt(pow(this->x(), 2) + pow(this->y(), 2) + pow(this->z(), 2));
}

vector3D vector3D::normalize()
{
    double base = this->module();
    vector3D result(this->x()/base, this->y()/base, this->z()/base);
    return result;
}

vector3D operator * (double scale, vector3D v)
{
    vector3D result(scale * v.x(), scale * v.y(), scale * v.z());
    return result;
}

vector3D operator - (vector3D v)
{
    vector3D result((-1) * v.x(), (-1) * v.y(), (-1) * v.z());
    return result;
}

vector3D crossProduct(vector3D v1, vector3D v2)
{
    double res_x = v1.y() * v2.z() - v1.z() * v2.y();
    double res_y = v1.z() * v2.x() - v1.x() * v2.z();
    double res_z = v1.x() * v2.y() - v1.y() * v2.x();
    vector3D result(res_x, res_y, res_z);
    return result;
}

double scalarProduct(vector3D v1, vector3D v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

double cosVectorialAngle(vector3D v1, vector3D v2)
{
    return scalarProduct(v1, v2) / (v1.module() * v2.module());
}
