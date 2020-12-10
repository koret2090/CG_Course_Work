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
using namespace std;

class Earth
{
public:
    Earth();
    ~Earth();
    int points_amount;
    Point* points;
    void turn_around_ox(double angle);
    void turn_around_oy(double angle);
    void turn_around_oz(double angle);

private:
    void init_earth();
};

#endif // EARTH_H
