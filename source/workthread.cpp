#include "workthread.h"
#include <QDebug>

WorkThread::WorkThread(PathTracing *path_tracing, QObject *parent) : QThread(parent)
{
    this->pt = path_tracing;
    //qDebug() << "Worker Thread : " << QThread::currentThreadId();
}

WorkThread::~WorkThread()
{
    requestInterruption();
    quit();
    wait();
}

void WorkThread::run()
{
    // This part is same as PathTracing::render()
    // To use process bar, move the codes here.
    double gamma = 2.2;
    vector<vector<vector3D>> imageRGB(static_cast<unsigned int>(pt->camera->width), vector<vector3D>(static_cast<unsigned int>(pt->camera->height), vector3D(0, 0, 0)));
    for(int i = 0; i < pt->camera->width; i++){
        for(int j = 0; j < pt->camera->height; j++){
            vector3D rgb;
            for(int k = 0; k < pt->numRayinPixel; k++){
                Ray pixelSampleRay = pt->camera->genRay(i, j);
                Intersection itsn;
                rgb = rgb + pt->rayTracing(pixelSampleRay, 0);
            }
            rgb = rgb / double(pt->numRayinPixel);
            for(int k = 0; k < 3; k++){
                rgb[k] = pow(double(rgb[k]), 1.0 / gamma);
                rgb[k] = (rgb[k] > 0.999) ? 0.999 : rgb[k];
                rgb[k] = (rgb[k] < 0) ? 0 : rgb[k];
                rgb[k] = 255 * rgb[k];
            }
            imageRGB[static_cast<unsigned int>(i)][static_cast<unsigned int>(j)] = rgb;
        }
        //cout << double(i + 1) / double(pt->camera->height) * 100 << "%" << endl;
        double percentage = double(i + 1) / double(pt->camera->width);
        emit resultReady(percentage);
    }
    pt->image = imageRGB;
    this->renderover = true;
}
