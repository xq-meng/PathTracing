#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include <QDialog>
#include "matrix.h"
#include "lightpanel.h"

namespace Ui {
class settingpanel;
}

class settingpanel : public QDialog
{
    Q_OBJECT

public:
    explicit settingpanel(QWidget *parent = nullptr);
    ~settingpanel();
    bool        isSet = false;
    vector3D    camera_position;
    vector3D    camera_lookat;
    vector3D    camera_up;
    double      camera_fov;
    double      camera_width;
    double      camera_height;
    vector3D    light_position;
    vector3D    light_emission;
    double      light_radius = -1;
    int         pixel_ray_num;
    int         light_ray_num;
    int         depth;
    vector3D    ambient_light;

    lightpanel  *lp;

private slots:
    void on_rb_conel_clicked(bool checked);

    void on_rb_dining_clicked(bool checked);

    void on_rb_veach_clicked(bool checked);

    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::settingpanel *ui;
};

#endif // SETTINGPANEL_H
