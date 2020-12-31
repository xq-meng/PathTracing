#ifndef VISUALWINDOW_H
#define VISUALWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include "matrix.h"

#define WINWIDTH 512
#define WINHEIGHT 512

class VisualWindow : public QWidget {
public:
    VisualWindow(int width, int height, QWidget* parent = nullptr);

    QRgb    *color;
    int     width;
    int     height;

    void paintEvent(QPaintEvent*);
    void setPixel(uint i, uint j, QRgb c);
    void paintImage(vector<vector<vector3D>> imageRGB);
};

#endif // VISUALWINDOW_H
