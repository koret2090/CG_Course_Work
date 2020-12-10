#ifndef EARTH_H
#define EARTH_H

#include <vector>
#include "points.h"
#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QtWidgets>
#include "trajectory.h"
#include <fstream>

using namespace std;

class Earth
{
public:
    Earth();
    ~Earth();
    size_t points_amount;
    Point* points;
    Trajectory trajectories[TRAJECTORY_AMOUNT];
    size_t trajectories_amount;

    void turn_around_ox(double angle);
    void turn_around_oy(double angle);
    void turn_around_oz(double angle);

private:
    void init_earth();
    void init_trajectories();
};

#endif // EARTH_H
