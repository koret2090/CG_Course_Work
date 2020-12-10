#include "earth.h"

Earth::Earth()
{
    points_amount = 0;
    points = (Point*)malloc(POINTS_AMOUNT * sizeof(Point));
    init_earth();
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
}

void Earth::turn_around_ox(double angle)
{
    for (int i = 0; i < points_amount; i++)
        turn_around_x(points[i], angle);
}

void Earth::turn_around_oy(double angle)
{
    for (int i = 0; i < points_amount; i++)
        turn_around_y(points[i], angle);
}

void Earth::turn_around_oz(double angle)
{
    for (int i = 0; i < points_amount; i++)
        turn_around_z(points[i], angle);
}
