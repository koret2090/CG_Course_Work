#ifndef EARTHOGL_H
#define EARTHOGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QtGui>
#include <sys/stat.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "consts.h"
#include <fstream>
#include "points.h"
#include "trajectory.h"

class EarthOGL : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit EarthOGL(QWidget *parent = nullptr);
    Trajectory trajectories[TRAJECTORY_AMOUNT];
    size_t trajectories_amount;
    int path_point;
    int step;

    void set_new_speed(int speed);

private slots:
     void path_point_counter();

private:
    GLfloat x_rot;
    GLfloat z_rot;
    GLuint texture[3];
    GLUquadric* m_obj;
    QPoint prs_pos;

    void draw_earth();
    void draw_sphere();
    void gen_textures();
    void flight();
    double scale;

    bool flag;

    void init_trajectories();
    void draw_trajectories();


    QTimer* paint_timer;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent* pe);
    virtual void mouseMoveEvent (QMouseEvent* pe);
    virtual void wheelEvent(QWheelEvent *pe);


};

#endif // EARTHOGL_H
