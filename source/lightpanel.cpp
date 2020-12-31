#include "lightpanel.h"
#include "ui_lightpanel.h"

lightpanel::lightpanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lightpanel)
{
    ui->setupUi(this);
}

lightpanel::~lightpanel()
{
    delete ui;
}

void lightpanel::on_pushButton_clicked()
{
    double lp_x = this->ui->lgt_ps_x->text().toDouble();
    double lp_y = this->ui->lgt_ps_y->text().toDouble();
    double lp_z = this->ui->lgt_ps_z->text().toDouble();
    double le_x = this->ui->lgt_em_x->text().toDouble();
    double le_y = this->ui->lgt_em_y->text().toDouble();
    double le_z = this->ui->lgt_em_z->text().toDouble();
    double lr_r = this->ui->lgt_rd_r->text().toDouble();
    vector3D light_position(lp_x, lp_y, lp_z);
    vector3D light_emission(le_x, le_y, le_z);
    this->light_position_list_added.push_back(light_position);
    this->light_emission_list_added.push_back(light_emission);
    this->light_radius_list_added.push_back(lr_r);
}
