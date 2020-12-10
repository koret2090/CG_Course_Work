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
    void draw_earth();

private slots:
    void on_up_btn_clicked();

    void on_down_btn_clicked();

    void on_left_btn_clicked();

    void on_right_btn_clicked();

    //void wheelEvent(QWheelEvent *pe);

    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
 
    QPen pen;
    QGraphicsScene *scene;
    Earth* earth;
    
    void draw_sphere();
    double scale;
};
#endif // MAINWINDOW_H
