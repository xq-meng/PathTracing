#ifndef LIGHTPANEL_H
#define LIGHTPANEL_H

#include <QDialog>
#include <vector>
#include "lightsource.h"
using namespace std;

namespace Ui {
class lightpanel;
}

class lightpanel : public QDialog
{
    Q_OBJECT

public:
    explicit lightpanel(QWidget *parent = nullptr);
    ~lightpanel();

    vector<vector3D>    light_position_list_added;
    vector<vector3D>    light_emission_list_added;
    vector<double>      light_radius_list_added;

private slots:
    void on_pushButton_clicked();

private:
    Ui::lightpanel *ui;
};

#endif // LIGHTPANEL_H
