#include "camera.h"

Camera::Camera()
{

}

void Camera::initialize(vector3D camera_position, vector3D camera_lookAt, vector3D camera_up)
{
    this->position = camera_position;
    this->lookAt = camera_lookAt;
    this->up = camera_up;
    this->right = crossProduct(camera_lookAt - camera_position, camera_up).normalize();
    this->up = crossProduct(this->right, camera_lookAt - camera_position).normalize();
}


void Camera::setViewPort(double camera_width, double camera_height, double camera_viewAngle)
{
    const double PI = acos(-1);
    this->width = camera_width;
    this->height = camera_height;
    this->viewAngle = camera_viewAngle;
    this->clipPortHeight = 2.0 * tan(camera_viewAngle / 2 * PI / 180.0) * ((this->lookAt - this->position).module());
    this->clipPortWidth = this->clipPortHeight / this->height * this->width;
    this->clipRatio = this->clipPortHeight / this->height;
}

Ray Camera::genRay(int x, int y)
{
    double screenCenterX = this->width / 2.0;
    double screenCenterY = this->height / 2.0;
    vector3D samplePoint =  this->lookAt
                            + (double(x) - screenCenterX/* + double(rand()) / double(RAND_MAX)*/) * this->clipRatio * this->right
                            + (double(y) - screenCenterY/* + double(rand()) / double(RAND_MAX)*/) * this->clipRatio * this->up;
    vector3D rayDirection = (samplePoint - this->position).normalize();
    Ray sampleRay(this->position, rayDirection);
    return sampleRay;
}
