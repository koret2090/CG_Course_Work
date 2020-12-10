#include "points.h"
#include <math.h>

double to_rad(double degrees)
{
    return degrees * M_PI / 180.0;
}

Point geo_to_rect(Point &point)
{
    Point result_point = {0, 0, 0};

    double radius_curvature = EQUATOR_RAD / sqrt(
                1.0 - SQR_ECCENTRICITY * sin(to_rad(point.x)) *
                sin(to_rad(point.x)));

    result_point.x = (radius_curvature + point.z) * cos(to_rad(point.x)) \
                                    * cos(to_rad(point.y));
    result_point.y = (radius_curvature + point.z) * cos(to_rad(point.x)) \
            * sin(to_rad(point.y));

    //result_point.z = (radius_curvature * (EQUATOR_RAD * EQUATOR_RAD / POLAR_RAD / POLAR_RAD)
    //                   + point.z) * sin(to_rad(point.x));

    result_point.z = (radius_curvature * (1.0 - SQR_ECCENTRICITY) + point.z)\
            * sin(to_rad(point.x));

    return result_point;
}

void turn_around_x(Point &point, double angle)
{
    double y0 = point.y;
    double z0 = point.z;

    point.y = y0 * cos(to_rad(angle)) - z0 * sin(to_rad(angle));
    point.z = y0 * sin(to_rad(angle)) + z0 * cos(to_rad(angle));
}

void turn_around_y(Point &point, double angle)
{
    double x0 = point.x;
    double z0 = point.z;

    point.x = x0 * cos(to_rad(angle)) + z0 * sin(to_rad(angle));
    point.z = -x0 * sin(to_rad(angle)) + z0 * cos(to_rad(angle));
}

void turn_around_z(Point &point, double angle)
{
    double x0 = point.x;
    double y0 = point.y;

    point.x = x0 * cos(to_rad(angle)) - y0 * sin(to_rad(angle));
    point.y = x0 * sin(to_rad(angle)) + y0 * cos(to_rad(angle));
}

void scale(Point &point, double k)
{
    point.x *= k;
    point.y *= k;
    point.z *= k;
}

void draw_point(QGraphicsScene *scene, QPen &pen, Point &point)
{
    scene->addLine(point.x, point.y, point.x, point.y, pen);
}
