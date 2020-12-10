#include "earthogl.h"

EarthOGL::EarthOGL(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,800);
    scale = SCALE;
}

void EarthOGL:: initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
}

void EarthOGL:: resizeGL(int nWidth, int nHeight)
{
  glViewport(0,0,nWidth,nHeight);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
}

void EarthOGL:: paintGL()
{
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  //glBindTexture(GL_TEXTURE_2D, texture[1]);
  glLoadIdentity();
  glTranslatef(0.0,0.0,-3.0);
  glRotatef(x_rot,1.0,0.0,0.0);
  glRotatef(y_rot,0.0,1.0,0.0);

  // линии широт и долгот
  draw_earth();

  // отрисовка траекторий

  // наложение текстур
  draw_sphere();
  gen_textures();
}

void EarthOGL:: gen_textures()
{
    /*
    //texture[0]=bindTexture(QPixmap(QString(":/textures/zemlya.bmp")), GL_TEXTURE_2D);
    texture[0]=bindTexture(QPixmap(QString("zemlya.bmp")), GL_TEXTURE_2D);
    texture[0] = bindTe
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    */
    glGenTextures(1, texture);

    QImage texture1;
    texture1.load("zemlya.bmp");

    texture1 = texture1.convertToFormat(QImage::Format_RGBA8888); // формат текстуры OpenGL

    glBindTexture(GL_TEXTURE_2D, texture[0]); // привязываю текстуру GL_Texture_2d к участку памяти texture[index]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // параметры фильтрации
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()),
        GLsizei(texture1.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits()); // заливаю текстуру
    glEnd();
}


void EarthOGL:: draw_sphere()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);

    //gen_textures();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glRotatef(-120.0,0,0,1);
    //qglColor(Qt::white);
    glColor4d(1, 1, 1, 1);

    m_obj = gluNewQuadric();

    gluQuadricTexture(m_obj,GL_TRUE);
    gluSphere(m_obj,(EQUATOR_RAD - 200000) * scale,36,36);


    glPushMatrix();

    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_ALPHA_TEST);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void EarthOGL:: draw_earth()
{
    glBegin(GL_LINES);
    glColor4d(1, 1, 1, 1);

    // строим широты и долготы
    double h = 0;
    for (double lon = 0; lon < 360; lon += 10)
      {
        for (double lat = 0; lat < 360; lat += 10)
          {
            Point point = {lat, lon, h};
            Point coords = geo_to_rect(point);

            glVertex3f(coords.x * scale, coords.y * scale, coords.z * scale);
          }
      }
    glEnd();

    for (double lat = 0; lat < 360; lat += 10)
      {
        glBegin(GL_LINE_STRIP);
        glColor4d(1, 1, 1, 1);
        for (double lon = 0; lon < 360; lon += 10)
          {
            Point point = {lat, lon, h};
            Point coords = geo_to_rect(point);

            glVertex3f(coords.x * scale, coords.y * scale, coords.z * scale);
          }
        glEnd();
      }
}


void EarthOGL:: mousePressEvent(QMouseEvent *pe)
{
  prs_pos = pe->pos();
}

void EarthOGL:: mouseMoveEvent(QMouseEvent *pe)
{
  x_rot += 180*(GLfloat)(pe->y()-prs_pos.y())/height();
  y_rot += 180*(GLfloat)(pe->x()-prs_pos.x())/width();

  //update();
  repaint();
  prs_pos = pe->pos();
}

void EarthOGL:: wheelEvent(QWheelEvent *pe)
{
  if ((pe->delta()) > 0)
      scale *= 1.1;
  else if ((pe->delta()) < 0)
      scale /= 1.1;

  //update();
  repaint();
}

