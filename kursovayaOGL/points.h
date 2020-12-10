#ifndef POINTS_H
#define POINTS_H

#include <cmath>
#include "consts.h"
#include <vector>
#include <QGraphicsScene>

using namespace std;


typedef struct Point
{
    double x;
    double y;
    double z;
} Point;


double to_rad(double degrees);
Point geo_to_rect(Point &point);
void draw_point(QGraphicsScene *scene, QPen &pen, Point &point);

void turn_around_x(Point &point, double angle);
void turn_around_y(Point &point, double angle);
void turn_around_z(Point &point, double angle);

#endif // POINTS_H
