#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sp = new settingpanel(this);
    this->setWindowTitle("Path Tracing");
    this->ui->pushButton->setMaximumSize(100,30);
    this->ui->pushButton->setDisabled(true);
    this->ui->filelabel->setText("Please load your obj file.");
    QString authorInfo1 = "School of Aeronautics and Astronautics";
    QString authorInfo2 = "Xiangqiao Meng: 21924044 | E-mail: xqmeng@zju.edu.cn\n";
    ui->textBrowser->append(authorInfo1);
    ui->textBrowser->append(authorInfo2);
    //ui->widget->setMinimumHeight(WINHEIGHT);
    //ui->widget->setMinimumWidth(WINWIDTH);
    //this->setMaximumHeight(WINHEIGHT + 250);
    //this->setMinimumHeight(WINHEIGHT + 250);
    //this->setMaximumWidth(WINWIDTH);
    //this->setMinimumWidth(WINWIDTH);
    this->ui->progressBar->hide();
    this->ui->progressBar->setValue(0);
    //vw = new VisualWindow(512, 512, ui->widget);
    pt = new PathTracing();

    // unit test
}

MainWindow::~MainWindow()
{
    delete vw;
    delete pt;
    delete wt;
    delete ui;
}


void MainWindow::on_actionLoad_Obj_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Open 3D Model"),"", tr("Object Files (*.obj)"));
    //QString filename = "/home/mxq/codes/PathTracing/examples/room/room.obj";
    if(filename.isEmpty())
        return;
    ui->textBrowser->append(filename);
    std::string stdfilename = filename.toStdString();
    this->pt->frame->load_obj(stdfilename);
    this->ui->pushButton->setDisabled(false);
    this->ui->filelabel->setText(filename);

    // for cornell box debug
    /*
    vector3D light_center(0, 0, 0);
    int light_count = 0;
    double light_max_x = -99999;
    double light_min_x = 99999;
    double light_max_y = -99999;
    double light_min_y = 99999;
    double light_max_z = -99999;
    double light_min_z = 99999;
    for(unsigned int i = 0; i < pt->frame->elems.size(); i++){
        if(abs(pt->frame->elems[i]->material->Ka.y() - 10.0) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light_center = light_center + facet_center;
            light_count++;
            light_max_x = (light_max_x > pt->frame->elems[i]->vertice_position[0].x()) ? light_max_x : pt->frame->elems[i]->vertice_position[0].x();
            light_min_x = (light_min_x < pt->frame->elems[i]->vertice_position[0].x()) ? light_min_x : pt->frame->elems[i]->vertice_position[0].x();
            light_max_y = (light_max_y > pt->frame->elems[i]->vertice_position[0].y()) ? light_max_y : pt->frame->elems[i]->vertice_position[0].y();
            light_min_y = (light_min_y < pt->frame->elems[i]->vertice_position[0].y()) ? light_min_y : pt->frame->elems[i]->vertice_position[0].y();
            light_max_z = (light_max_z > pt->frame->elems[i]->vertice_position[0].z()) ? light_max_z : pt->frame->elems[i]->vertice_position[0].z();
            light_min_z = (light_min_z < pt->frame->elems[i]->vertice_position[0].z()) ? light_min_z : pt->frame->elems[i]->vertice_position[0].z();
            light_max_x = (light_max_x > pt->frame->elems[i]->vertice_position[1].x()) ? light_max_x : pt->frame->elems[i]->vertice_position[1].x();
            light_min_x = (light_min_x < pt->frame->elems[i]->vertice_position[1].x()) ? light_min_x : pt->frame->elems[i]->vertice_position[1].x();
            light_max_y = (light_max_y > pt->frame->elems[i]->vertice_position[1].y()) ? light_max_y : pt->frame->elems[i]->vertice_position[1].y();
            light_min_y = (light_min_y < pt->frame->elems[i]->vertice_position[1].y()) ? light_min_y : pt->frame->elems[i]->vertice_position[1].y();
            light_max_z = (light_max_z > pt->frame->elems[i]->vertice_position[1].z()) ? light_max_z : pt->frame->elems[i]->vertice_position[1].z();
            light_min_z = (light_min_z < pt->frame->elems[i]->vertice_position[1].z()) ? light_min_z : pt->frame->elems[i]->vertice_position[1].z();
            light_max_x = (light_max_x > pt->frame->elems[i]->vertice_position[2].x()) ? light_max_x : pt->frame->elems[i]->vertice_position[2].x();
            light_min_x = (light_min_x < pt->frame->elems[i]->vertice_position[2].x()) ? light_min_x : pt->frame->elems[i]->vertice_position[2].x();
            light_max_y = (light_max_y > pt->frame->elems[i]->vertice_position[2].y()) ? light_max_y : pt->frame->elems[i]->vertice_position[2].y();
            light_min_y = (light_min_y < pt->frame->elems[i]->vertice_position[2].y()) ? light_min_y : pt->frame->elems[i]->vertice_position[2].y();
            light_max_z = (light_max_z > pt->frame->elems[i]->vertice_position[2].z()) ? light_max_z : pt->frame->elems[i]->vertice_position[2].z();
            light_min_z = (light_min_z < pt->frame->elems[i]->vertice_position[2].z()) ? light_min_z : pt->frame->elems[i]->vertice_position[2].z();
        }
    }
    light_center = light_center / light_count;
    this->ui->textBrowser->append("light: " + QString::number(light_center[0]) + " " + QString::number(light_center[1]) + " " + QString::number(light_center[2]));
    this->ui->textBrowser->append("light min: " + QString::number(light_min_x) + " " + QString::number(light_min_y) + " " + QString::number(light_min_z));
    this->ui->textBrowser->append("light max: " + QString::number(light_max_x) + " " + QString::number(light_max_y) + " " + QString::number(light_max_z));
    */
    // for dining room debug
    /*
    vector3D light1_center(0, 0, 0);    double light1_count = 0;
    vector3D light2_center(0, 0, 0);    double light2_count = 0;
    double light1_max_x = -99999;
    double light2_max_x = -99999;
    double light1_min_x = 99999;
    double light2_min_x = 99999;
    for(unsigned int i = 0; i < pt->frame->elems.size(); i++){
        if(abs(pt->frame->elems[i]->material->Ka.y() - 20.0) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light1_center = light1_center + facet_center;
            light1_max_x = (light1_max_x > pt->frame->elems[i]->vertice_position[0].x()) ? light1_max_x : pt->frame->elems[i]->vertice_position[0].x();
            light1_min_x = (light1_min_x < pt->frame->elems[i]->vertice_position[0].x()) ? light1_min_x : pt->frame->elems[i]->vertice_position[0].x();
            light1_count++;
        }
        if(abs(pt->frame->elems[i]->material->Ka.z() - 20.0) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light2_center = light2_center + facet_center;
            light2_max_x = (light2_max_x > pt->frame->elems[i]->vertice_position[0].x()) ? light2_max_x : pt->frame->elems[i]->vertice_position[0].x();
            light2_min_x = (light2_min_x < pt->frame->elems[i]->vertice_position[0].x()) ? light2_min_x : pt->frame->elems[i]->vertice_position[0].x();
            light2_count++;
        }
    }
    light1_center = light1_center / light1_count;
    light2_center = light2_center / light2_count;
    this->ui->textBrowser->append("light1: " + QString::number(light1_center[0]) + " " + QString::number(light1_center[1]) + " " + QString::number(light1_center[2]));
    this->ui->textBrowser->append("light2: " + QString::number(light2_center[0]) + " " + QString::number(light2_center[1]) + " " + QString::number(light2_center[2]));
    this->ui->textBrowser->append("light1 radius: " + QString::number(light1_max_x - light1_min_x));
    this->ui->textBrowser->append("light2 radius: " + QString::number(light2_max_x - light2_min_x));
    */
    // for veach mis debug
    /*
    vector3D light1_center(0, 0, 0);    double light1_count = 0;
    vector3D light2_center(0, 0, 0);    double light2_count = 0;
    vector3D light3_center(0, 0, 0);    double light3_count = 0;
    vector3D light4_center(0, 0, 0);    double light4_count = 0;
    vector3D light5_center(0, 0, 0);    double light5_count = 0;
    for(unsigned int i = 0; i < pt->frame->elems.size(); i++){
        if(abs(pt->frame->elems[i]->material->Ka.x() - 901.8) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light1_center = light1_center + facet_center;
            light1_count++;
        }
        if(abs(pt->frame->elems[i]->material->Ka.x() - 100.0) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light2_center = light2_center + facet_center;
            light2_count++;
        }
        if(abs(pt->frame->elems[i]->material->Ka.x() - 11.11) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light3_center = light3_center + facet_center;
            light3_count++;
        }
        if(abs(pt->frame->elems[i]->material->Ka.x() - 1.24) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light4_center = light4_center + facet_center;
            light4_count++;
        }
        if(abs(pt->frame->elems[i]->material->Ka.x() - 800.0) < 0.01){
            vector3D facet_center = pt->frame->elems[i]->vertice_position[0] + pt->frame->elems[i]->vertice_position[1] + pt->frame->elems[i]->vertice_position[2];
            facet_center = facet_center / 3;
            light5_center = light5_center + facet_center;
            light5_count++;
        }
    }
    light1_center = light1_center / light1_count;
    light2_center = light2_center / light2_count;
    light3_center = light3_center / light3_count;
    light4_center = light4_center / light4_count;
    light5_center = light5_center / light5_count;
    this->ui->textBrowser->append("light1: " + QString::number(light1_center[0]) + " " + QString::number(light1_center[1]) + " " + QString::number(light1_center[2]));
    this->ui->textBrowser->append("light2: " + QString::number(light2_center[0]) + " " + QString::number(light2_center[1]) + " " + QString::number(light2_center[2]));
    this->ui->textBrowser->append("light3: " + QString::number(light3_center[0]) + " " + QString::number(light3_center[1]) + " " + QString::number(light3_center[2]));
    this->ui->textBrowser->append("light4: " + QString::number(light4_center[0]) + " " + QString::number(light4_center[1]) + " " + QString::number(light4_center[2]));
    this->ui->textBrowser->append("light5: " + QString::number(light5_center[0]) + " " + QString::number(light5_center[1]) + " " + QString::number(light5_center[2]));
    */
}

void MainWindow::on_actionSetting_Panel_triggered()
{
    sp->setModal(true);
    sp->show();
}

void MainWindow::on_pushButton_clicked()
{
    if(!this->sp->isSet){
        ui->textBrowser->append("Please set your render parameter in \"Start\" menu.");
    }
    else{
        ui->textBrowser->append("Bgein rendering...");
        this->pt->camera->initialize(this->sp->camera_position, this->sp->camera_lookat, this->sp->camera_up);
        this->pt->camera->setViewPort(this->sp->camera_width, this->sp->camera_height, this->sp->camera_fov);
        LightSource* sphere_light = new LightSource();
        sphere_light->setLight(this->sp->light_position, this->sp->light_emission, this->sp->light_radius);
        this->pt->frame->lights.push_back(sphere_light);
        unsigned int added_light_num = static_cast<unsigned int>(this->sp->lp->light_radius_list_added.size());
        for(unsigned int i = 0; i < added_light_num; i++){
            LightSource* added_sphere_light = new LightSource();
            added_sphere_light->setLight(sp->lp->light_position_list_added[i], sp->lp->light_emission_list_added[i], sp->lp->light_radius_list_added[i]);
            this->pt->frame->lights.push_back(added_sphere_light);
        }
        this->pt->numRayinPixel = this->sp->pixel_ray_num;
        this->pt->numSmpinLight = this->sp->light_ray_num;
        this->pt->maxDepth = this->sp->depth;
        this->pt->ambientLight = this->sp->ambient_light;
        this->ui->progressBar->show();
        this->ui->progressBar->update();

        // update mainwindow layout
        int vw_width = static_cast<int>(this->pt->camera->width);
        int vw_height = static_cast<int>(this->pt->camera->height);
        vw = new VisualWindow(vw_width, vw_height, this->ui->widget);
        QHBoxLayout* vw_layout = new QHBoxLayout(ui->widget);
        vw_layout->addWidget(vw);
        this->ui->widget->setLayout(vw_layout);
        this->ui->widget->setMinimumWidth(vw_width);
        this->ui->widget->setMinimumHeight(vw_height);
        this->ui->widget->setMaximumWidth(vw_width);
        this->setMaximumWidth(vw_width);

        // start new work thread, begin rendering
        startWorkThread();
    }
}

void MainWindow::startWorkThread()
{
    wt = new WorkThread(this->pt, this);
    connect(wt, SIGNAL(resultReady(double)), this, SLOT(handleResults(double)));
    connect(wt, SIGNAL(finished()), this, SLOT(drawImage()));
    connect(wt, SIGNAL(finished()), wt, SLOT(deleteLater()));
    wt->start();
}

void MainWindow::handleResults(double value)
{
    this->ui->progressBar->setValue(static_cast<int>(value * 100));
    //this->ui->progressBar->update();
}

void MainWindow::drawImage()
{
    this->ui->textBrowser->append("Finish rendering.");
    this->vw->paintImage(this->pt->image);
    this->vw->update();
}
