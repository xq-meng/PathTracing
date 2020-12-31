#include "settingpanel.h"
#include "ui_settingpanel.h"

settingpanel::settingpanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingpanel)
{
    ui->setupUi(this);
    this->setWindowTitle("Setting Panel");
    lp = new lightpanel(this);
    lp->setModal(true);
}

settingpanel::~settingpanel()
{
    delete ui;
}

void settingpanel::on_rb_conel_clicked(bool checked)
{
    // set default light source
    this->ui->lgt_ps_x->setText("278");
    this->ui->lgt_ps_y->setText("530");
    this->ui->lgt_ps_z->setText("279.5");
    this->ui->lgt_em_x->setText("10");
    this->ui->lgt_em_y->setText("10");
    this->ui->lgt_em_z->setText("10");
    this->ui->lgt_rd_r->setText("20");

    // set default camera
    this->ui->cma_ps_x->setText("278");
    this->ui->cma_ps_y->setText("273");
    this->ui->cma_ps_z->setText("-800");
    this->ui->cma_la_x->setText("278");
    this->ui->cma_la_y->setText("273");
    this->ui->cma_la_z->setText("-799");
    this->ui->cma_up_x->setText("0");
    this->ui->cma_up_y->setText("1");
    this->ui->cma_up_z->setText("0");
    this->ui->cma_fa_l->setText("40");
    this->ui->cma_sz_hg->setText("512");
    this->ui->cma_sz_wd->setText("512");

    // set default path tracing parameter
    this->ui->pt_nr_lgt_n->setText("1");
    this->ui->pt_nr_pix_n->setText("1");
    this->ui->pt_dp_n->setText("10");
    this->ui->pt_aml_x->setText("1");
    this->ui->pt_aml_y->setText("1");
    this->ui->pt_aml_z->setText("1");

    /*
    // set default light source
    this->ui->lgt_ps_x->setText("0");
    this->ui->lgt_ps_y->setText("1.589");
    this->ui->lgt_ps_z->setText("-1.274");
    this->ui->lgt_em_x->setText("50");
    this->ui->lgt_em_y->setText("50");
    this->ui->lgt_em_z->setText("40");
    this->ui->lgt_rd_r->setText("0.2");
>>>>>>> 04b80db2d63603c9cbfabbf0b0a4b0206838202e

    // set default camera
    this->ui->cma_ps_x->setText("278");
    this->ui->cma_ps_y->setText("273");
    this->ui->cma_ps_z->setText("-800");
    this->ui->cma_la_x->setText("278");
    this->ui->cma_la_y->setText("273");
    this->ui->cma_la_z->setText("-799");
    this->ui->cma_up_x->setText("0");
    this->ui->cma_up_y->setText("1");
    this->ui->cma_up_z->setText("0");
    this->ui->cma_fa_l->setText("40");
    this->ui->cma_sz_hg->setText("512");
    this->ui->cma_sz_wd->setText("512");

    // set default path tracing parameter
    this->ui->pt_nr_lgt_n->setText("2");
    this->ui->pt_nr_pix_n->setText("2");
    this->ui->pt_dp_n->setText("10");
    this->ui->pt_aml_x->setText("1");
    this->ui->pt_aml_y->setText("1");
    this->ui->pt_aml_z->setText("1");
    */
}

void settingpanel::on_rb_dining_clicked(bool checked)
{
    // set default light source
    this->ui->lgt_ps_x->setText("-2.2");
    this->ui->lgt_ps_y->setText("3.6");
    this->ui->lgt_ps_z->setText("-2");
    this->ui->lgt_em_x->setText("20");
    this->ui->lgt_em_y->setText("20");
    this->ui->lgt_em_z->setText("10");
    this->ui->lgt_rd_r->setText("0.6");

    // add more light source
    this->lp->light_position_list_added.push_back(vector3D(0.95, 3.6, -2));
    this->lp->light_emission_list_added.push_back(vector3D(20, 10, 20));
    this->lp->light_radius_list_added.push_back(0.6);

    // set default camera
    this->ui->cma_ps_x->setText("-0.5");
    this->ui->cma_ps_y->setText("3");
    this->ui->cma_ps_z->setText("5.5");
    this->ui->cma_la_x->setText("-0.5");
    this->ui->cma_la_y->setText("2");
    this->ui->cma_la_z->setText("0");
    this->ui->cma_up_x->setText("0");
    this->ui->cma_up_y->setText("1");
    this->ui->cma_up_z->setText("0");
    this->ui->cma_fa_l->setText("35");
    this->ui->cma_sz_hg->setText("720");
    this->ui->cma_sz_wd->setText("1280");

    // set default path tracing parameter
    this->ui->pt_nr_lgt_n->setText("10");
    this->ui->pt_nr_pix_n->setText("50");
    this->ui->pt_dp_n->setText("5");
    this->ui->pt_aml_x->setText("1");
    this->ui->pt_aml_y->setText("1");
    this->ui->pt_aml_z->setText("1");
}

void settingpanel::on_rb_veach_clicked(bool checked)
{
    // set default light source
    this->ui->lgt_ps_x->setText("10");
    this->ui->lgt_ps_y->setText("10");
    this->ui->lgt_ps_z->setText("4");
    this->ui->lgt_em_x->setText("800");
    this->ui->lgt_em_y->setText("800");
    this->ui->lgt_em_z->setText("800");
    this->ui->lgt_rd_r->setText("0.5");

    // add more light source
    this->lp->light_position_list_added.push_back(vector3D(-3.75, 0, 0));
    this->lp->light_position_list_added.push_back(vector3D(-1.25, 0, 0));
    this->lp->light_position_list_added.push_back(vector3D(1.25, 0, 0));
    this->lp->light_position_list_added.push_back(vector3D(3.75, 0, 0));
    this->lp->light_emission_list_added.push_back(vector3D(901.80, 901.80, 901.80));
    this->lp->light_emission_list_added.push_back(vector3D(100, 100, 100));
    this->lp->light_emission_list_added.push_back(vector3D(11.11, 11.11, 11.11));
    this->lp->light_emission_list_added.push_back(vector3D(1.24, 1.24, 1.24));
    this->lp->light_radius_list_added.push_back(0.033);
    this->lp->light_radius_list_added.push_back(0.1);
    this->lp->light_radius_list_added.push_back(0.3);
    this->lp->light_radius_list_added.push_back(0.9);

    // set default camera
    this->ui->cma_ps_x->setText("0");
    this->ui->cma_ps_y->setText("2");
    this->ui->cma_ps_z->setText("15");
    this->ui->cma_la_x->setText("0");
    this->ui->cma_la_y->setText("-2");
    this->ui->cma_la_z->setText("2.5");
    this->ui->cma_up_x->setText("0");
    this->ui->cma_up_y->setText("1");
    this->ui->cma_up_z->setText("0");
    this->ui->cma_fa_l->setText("28");
    this->ui->cma_sz_hg->setText("512");
    this->ui->cma_sz_wd->setText("768");

    // set default path tracing parameter
    this->ui->pt_nr_lgt_n->setText("25");
    this->ui->pt_nr_pix_n->setText("50");
    this->ui->pt_dp_n->setText("10");
    this->ui->pt_aml_x->setText("1");
    this->ui->pt_aml_y->setText("1");
    this->ui->pt_aml_z->setText("1");
}

void settingpanel::on_buttonBox_accepted()
{
    // set camera
    this->camera_position[0] = this->ui->cma_ps_x->text().toDouble();
    this->camera_position[1] = this->ui->cma_ps_y->text().toDouble();
    this->camera_position[2] = this->ui->cma_ps_z->text().toDouble();
    this->camera_lookat[0] = this->ui->cma_la_x->text().toDouble();
    this->camera_lookat[1] = this->ui->cma_la_y->text().toDouble();
    this->camera_lookat[2] = this->ui->cma_la_z->text().toDouble();
    this->camera_up[0] = this->ui->cma_up_x->text().toDouble();
    this->camera_up[1] = this->ui->cma_up_y->text().toDouble();
    this->camera_up[2] = this->ui->cma_up_z->text().toDouble();
    this->camera_fov = this->ui->cma_fa_l->text().toDouble();
    this->camera_height = this->ui->cma_sz_hg->text().toDouble();
    this->camera_width = this->ui->cma_sz_wd->text().toDouble();

    // set light source
    this->light_position[0] = this->ui->lgt_ps_x->text().toDouble();
    this->light_position[1] = this->ui->lgt_ps_y->text().toDouble();
    this->light_position[2] = this->ui->lgt_ps_z->text().toDouble();
    this->light_emission[0] = this->ui->lgt_em_x->text().toDouble();
    this->light_emission[1] = this->ui->lgt_em_y->text().toDouble();
    this->light_emission[2] = this->ui->lgt_em_z->text().toDouble();
    this->light_radius = this->ui->lgt_rd_r->text().toDouble();

    // set path tracing parameter
    this->depth = this->ui->pt_dp_n->text().toInt();
    this->light_ray_num = this->ui->pt_nr_lgt_n->text().toInt();
    this->pixel_ray_num = this->ui->pt_nr_pix_n->text().toInt();
    this->ambient_light[0] = this->ui->pt_aml_x->text().toDouble();
    this->ambient_light[1] = this->ui->pt_aml_y->text().toDouble();
    this->ambient_light[2] = this->ui->pt_aml_z->text().toDouble();

    this->isSet = true;
}

void settingpanel::on_pushButton_clicked()
{
    lp->show();
}
