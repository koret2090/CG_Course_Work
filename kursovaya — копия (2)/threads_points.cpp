#include "threads_points.h"

void convert_line(int start_row, int end_row, double scale, Earth* earth, QGraphicsScene *scene)
{
    for (int i = start_row; i < end_row; i += 2)
    {
     Point point1 = earth->points[i];
     Point point2 = earth->points[i + 1];
     scene->addLine(point1.x * scale + MOVE_X, point1.y * scale + MOVE_Y,
                    point2.x * scale + MOVE_X, point2.y * scale + MOVE_Y,
                    QPen(Qt::green));
    }
}
