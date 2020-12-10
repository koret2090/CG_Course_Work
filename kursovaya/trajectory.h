#ifndef TRAJECTORY_H
#define TRAJECTORY_H

#include "points.h"
#include <fstream>
class Trajectory
{
public:
    Trajectory();
    Trajectory(Point& start_point, Point& end_point);
    void copy_to(size_t& dest_id, Point *dest);
    void build2();
    size_t points_amount;
    Point points[150];

private:
    Point start_point;
    Point end_point;


    double parabola_equation_result(double a, double b, double x);
    void get_parabola_coefs(Point& point1, Point& point2, double& a, double& b);
    double get_fix_height(double coef_a);

};

#endif // TRAJECTORY_H
