#include "earth.h"

Earth::Earth()
{
    points_amount = 0;
    points = (Point*)malloc(POINTS_AMOUNT * sizeof(Point));
    trajectories_amount = TRAJECTORY_AMOUNT;
    init_earth();
    init_trajectories();
}

Earth::~Earth()
{
    free(points);
}

void Earth::init_earth()
{
    Point point_prev;
    point_prev.x = 0; point_prev.y = 0; point_prev.z = 0;


    double h = 0;
    for (double lon = 0; lon < 360; lon += 10)
    {
        for (double lat = 0; lat < 360-10; lat += 10)
        {
            Point point;
            point.x = lat; point.y = lon; point.z = h;
            Point coords = geo_to_rect(point);

            Point point2;
            point2.x = lat + 10; point2.y = lon; point2.z = h;
            Point coords2 = geo_to_rect(point2);

            points[points_amount] = coords;
            points_amount++;
            points[points_amount] = coords2;
            points_amount++;
        }
    }

    for (double lat = 0; lat < 360; lat += 10)
    {
        for (double lon = 0; lon < 360-10; lon += 10)
        {
            Point point = {lat, lon, h};
            point.x = lat; point.y = lon; point.z = h;

            Point coords = geo_to_rect(point);

            Point point2;
            point2.x = lat; point2.y = lon + 10; point2.z = h;
            Point coords2 = geo_to_rect(point2);

            points[points_amount] = coords;
            points_amount++;
            points[points_amount] = coords2;
            points_amount++;
        }
    }

    ifstream file;
    file.open("russia.txt");

    Point point;
    file >> point.x >> point.y;
    point.z = 0;

    while (!file.eof())
    {
        Point point;
        file >> point.x >> point.y;
        point.x *= -1; point.y *= 1;
        point.x += 0; point.y += 180;
        point.z = 0;
        Point coords2 = geo_to_rect(point);

        points[points_amount] = coords2;
        points_amount++;
    }

    file.close();
}

void Earth::init_trajectories()
{
    Point moscow = {55, 37, 0};
    Point sydney = {-33.8, 151, 0};
    Point new_york = {40.7, -74, 0};
    Point habarovsk = {48.48, 135, 0};

    Trajectory moscow_sydney = Trajectory(moscow, sydney);
    Trajectory moscow_new_york = Trajectory(moscow, new_york);
    Trajectory new_york_sydney = Trajectory(new_york, sydney);
    Trajectory moscow_habarovsk = Trajectory(habarovsk, moscow);

    trajectories[0] = moscow_sydney;
    trajectories[1] = moscow_new_york;
    trajectories[2] = new_york_sydney;
    trajectories[3] = moscow_habarovsk;
}

void Earth::turn_around_ox(double angle)
{
    for (size_t i = 0; i < points_amount; i++)
        turn_around_x(points[i], angle);

    for (size_t i = 0; i < trajectories_amount; i++)
    {
        for (size_t j = 0; j < trajectories[i].points_amount; j++)
        {
            turn_around_x(trajectories[i].points[j], angle);
        }
    }
}

void Earth::turn_around_oy(double angle)
{
    for (size_t i = 0; i < points_amount; i++)
        turn_around_y(points[i], angle);

    for (size_t i = 0; i < trajectories_amount; i++)
    {
        for (size_t j = 0; j < trajectories[i].points_amount; j++)
        {
            turn_around_y(trajectories[i].points[j], angle);
        }
    }
}

void Earth::turn_around_oz(double angle)
{
    for (size_t i = 0; i < points_amount; i++)
        turn_around_z(points[i], angle);

    for (size_t i = 0; i < trajectories_amount; i++)
    {
        for (size_t j = 0; j < trajectories[i].points_amount; j++)
        {
            turn_around_z(trajectories[i].points[j], angle);
        }
    }
}
