#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <iostream>
#include <fstream>
#include <string>
#include "settingpanel.h"
#include "visualwindow.h"
#include "pathtracing.h"
#include "workthread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    settingpanel    *sp;
    VisualWindow    *vw;
    PathTracing     *pt;

private slots:
    void on_actionLoad_Obj_triggered();
    void on_actionSetting_Panel_triggered();
    void on_pushButton_clicked();
    void startWorkThread();
    void handleResults(double value);
    void drawImage();

private:
    Ui::MainWindow *ui;
    WorkThread*     wt;
};
#endif // MAINWINDOW_H
