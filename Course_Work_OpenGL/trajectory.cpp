#include "trajectory.h"
#include <QDebug>
Trajectory::Trajectory()
{

}

Trajectory::Trajectory(Point& start_point, Point& end_point)
{
    this->start_point.x = start_point.x;
    this->start_point.y = start_point.y;
    this->start_point.z = start_point.z;

    this->end_point.x = end_point.x;
    this->end_point.y = end_point.y;
    this->end_point.z = end_point.z;

    points_amount = 0;
    selected = false;

    this->build();
}

bool Trajectory::is_selected()
{
    return selected;
}

void Trajectory::set_selection(bool flag)
{
    selected = flag;
}

double Trajectory::parabola_equation_result(double a, double b, double x)
{
    return a * x * x + b * x;
}

void Trajectory::get_parabola_coefs(Point& point1, Point& point2, double& a, double& b)
{
    double x1 = point1.x;
    double x2 = point2.x;
    double y1 = point1.y;
    double y2 = point2.y;

    a = (y2 - y1 * x2 / x1) / (x2 * x2 - x1 * x2);
    b = (y1 - x1 * x1 * a) / x1;
}

double Trajectory::get_fix_height(double coef_a)
{
    double min = parabola_equation_result(coef_a, 0, -TRAJECTORY_POINTS / 2);

    for (double j = -TRAJECTORY_POINTS / 2 + 1; j <= TRAJECTORY_POINTS / 2; j++)
    {
        double value = parabola_equation_result(coef_a, 0, j);
        if (min > value)
        {
            min = value;
        }
    }
    return abs(min);
}

void Trajectory::build()
{
    Point start_coords =this->start_point;
    Point end_coords = this->end_point;

    double x_step = abs(start_coords.x - end_coords.x) / TRAJECTORY_POINTS;
    double y_step = abs(start_coords.y - end_coords.y) / TRAJECTORY_POINTS;

    if (start_coords.x > end_coords.x)
        x_step *= -1;

    if (start_coords.y > end_coords.y)
        y_step *= -1;

    double coef_a = 0;
    double coef_b = 0;
    get_parabola_coefs(start_coords, end_coords, coef_a, coef_b);
    coef_a = -abs(coef_a);
    double fix_h = get_fix_height(coef_a);

    for (int i = 0; i <= TRAJECTORY_POINTS; i++)
    {
        Point point;
        point.x = start_coords.x + i * x_step;
        point.y = start_coords.y + i * y_step;
        point.z = (parabola_equation_result(coef_a, 0, i - TRAJECTORY_POINTS / 2) + fix_h) * H_SCALE;
        Point coords = geo_to_rect(point);
        points[i] = coords;
        points_amount++;
    }
}

void Trajectory::copy_to(size_t& dest_id, Point *dest)
{
    for (int i = 0; i < TRAJECTORY_POINTS; i++)
    {
        dest[dest_id] = points[i];
        dest_id++;
    }
}
