#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <iostream>
#include <QDebug>
#include <math.h>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QGraphicsView>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QtWidgets>

#include "points.h"
#include "earth.h"
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_earth(Earth* earth){this->earth = earth;}
    void init_trajectory_list();
    void draw_earth();
    void draw_trajectories();
    double temp;

private slots:
    void on_up_btn_clicked();

    void on_down_btn_clicked();

    void on_left_btn_clicked();

    void on_right_btn_clicked();

    void wheelEvent(QWheelEvent *pe);

    bool eventFilter(QObject *obj, QEvent *event);

    void on_show_trajectories_btn_clicked();

private:
    Ui::MainWindow *ui;
 
    QPen pen;
    QGraphicsScene *scene;
    Earth* earth;
    
    void draw_sphere();
    double scale;
    double x_rot;
    double y_rot;
    double x_rot_prev;
    double y_rot_prev;
    QPoint prs_pos;

    void mouseMoveEvent(QMouseEvent *pe);
    void mousePressEvent(QMouseEvent *pe);
};
#endif // MAINWINDOW_H
