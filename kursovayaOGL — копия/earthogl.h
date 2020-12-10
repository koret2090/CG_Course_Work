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

class EarthOGL : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit EarthOGL(QWidget *parent = nullptr);

signals:

private:
    GLfloat x_rot;
    GLfloat y_rot;
    GLuint texture[3];
    GLUquadric* m_obj;
    QPoint prs_pos;

    void draw_earth();
    void draw_sphere();
    void gen_textures();
    double scale;

protected:
  virtual void initializeGL();
  virtual void resizeGL(int nWidth, int nHeight);
  virtual void paintGL();
  virtual void mousePressEvent(QMouseEvent* pe);
  virtual void mouseMoveEvent (QMouseEvent* pe);
  virtual void wheelEvent(QWheelEvent *pe);

};

#endif // EARTHOGL_H
