#include "visualwindow.h"

VisualWindow::VisualWindow(int width, int height, QWidget* parent) : QWidget(parent)
{
    this->resize(parent->width(), parent->height());
    color = new QRgb[width * height];
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            color[i * width + j] = 0;
        }
    }
    this->width = width;
    this->height = height;
}

void VisualWindow::paintEvent(QPaintEvent *)
{
    QPainter patr;
    QImage paIm(this->width, this->height, QImage::Format_RGB32);
    patr.begin(&paIm);
    for(int i = 0; i < this->width; i++){
        for(int j = 0; j < this->height; j++){
            paIm.setPixel(i, j, color[i * this->height + j]);
        }
    }
    patr.end();
    patr.begin(this);
    patr.drawImage(0, 0, paIm);
    patr.end();
}

void VisualWindow::setPixel(uint i, uint j, QRgb c)
{
    color[(this->width - 1 - i) * this->height + j] = c;
}

void VisualWindow::paintImage(vector<vector<vector3D> > imageRGB)
{
    int imageWidth = static_cast<int>(imageRGB.size());
    int imageHeight = static_cast<int>(imageRGB[0].size());
    for(int i = 0; i < imageWidth; i++){
        for(int j = 0; j < imageHeight; j++){
            int red = static_cast<int>(imageRGB[imageWidth - i - 1][imageHeight - j - 1][0]);
            int green = static_cast<int>(imageRGB[imageWidth - i - 1][imageHeight - j - 1][1]);
            int blue = static_cast<int>(imageRGB[imageWidth - i - 1][imageHeight - j - 1][2]);
            QRgb color = qRgb(red, green, blue);
            this->setPixel(i, j, color);
        }
    }
    return;
}
