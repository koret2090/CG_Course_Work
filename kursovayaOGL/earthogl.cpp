#include "earthogl.h"

EarthOGL::EarthOGL(QWidget *parent) : QOpenGLWidget(parent)
{
    resize(800,800);
    scale = SCALE;
    flag = true;

    trajectories_amount = TRAJECTORY_AMOUNT;
    init_trajectories();

    paint_timer = new QTimer(this);
    connect(paint_timer, SIGNAL(timeout()), this, SLOT(path_point_counter()));
    paint_timer->start(START_FLIGHT_SPEED);
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
    glRotatef(z_rot,0.0,0.0,1.0);

    // линии широт и долгот
    draw_earth();

    // отрисовка траекторий
    draw_trajectories();

    // полеты
    flight();

    // наложение текстур
    draw_sphere();
}

void EarthOGL:: gen_textures()
{
    glGenTextures(1, texture);

    QImage texture1;
    texture1.load("earth.jpg");

    texture1 = texture1.convertToFormat(QImage::Format_RGBA8888); // формат текстуры OpenGL

    glBindTexture(GL_TEXTURE_2D, texture[0]); // привязываю текстуру GL_Texture_2d к участку памяти texture[index]
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // параметры фильтрации
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()),
        GLsizei(texture1.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture1.bits()); // заливаю текстуру

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

    if (flag)
        gen_textures();
    flag = false;

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glRotatef(-120.0,0,0,1);
    //qglColor(Qt::white);
    glColor4d(1, 1, 1, 1);

    m_obj = gluNewQuadric();

    gluQuadricTexture(m_obj,GL_TRUE);
    gluSphere(m_obj,(EQUATOR_RAD - 100000) * scale, 36, 36);


    glPushMatrix();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
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

void EarthOGL::init_trajectories() // сделать считывание с файла
{
    ifstream file;
    file.open("trajectories.txt");

    for (size_t i = 0; i < trajectories_amount && !file.eof(); i++)
    {
        Point point1, point2;
        file >> point1.x >> point1.y >> point1.z >>
                point2.x >> point2.y >> point2.z;

        trajectories[i] = Trajectory(point1, point2);
    }
    file.close();
}

void EarthOGL::draw_trajectories()
{
    glLineWidth(3);
    for (size_t i = 0; i < TRAJECTORY_AMOUNT; i++)
    {
        if (trajectories[i].is_selected())
        {
            glBegin(GL_LINE_STRIP);
            glColor4d(0, 1, 0, 1);
            for (size_t j = 0; j < trajectories[i].points_amount; j++)
            {
                Point coords = trajectories[i].points[j];
                glVertex3f(coords.x * scale, coords.y * scale, coords.z * scale);
            }
            glEnd();
        }
    }
    glLineWidth(1);
}

void EarthOGL:: path_point_counter()
{
    if (path_point == TRAJECTORY_POINTS - 5)
        step = -1;
    else if (path_point == 0)
        step = 1;

    path_point += step;
    repaint();
}

void EarthOGL:: flight()
{
    glLineWidth(10);
    glBegin(GL_LINES);

    glColor4d(1, 0, 0, 1);
    for (size_t i = 0; i < TRAJECTORY_AMOUNT; i++)
    {
        if (trajectories[i].is_selected())
        {
            Point coords = trajectories[i].points[path_point];
            Point coords2 = trajectories[i].points[path_point+5];
            glVertex3f(coords.x * scale, coords.y * scale, coords.z * scale + 0.01);
            glVertex3f(coords2.x * scale, coords2.y * scale, coords2.z * scale + 0.01);
        }
    }
    glEnd();
    glLineWidth(1);
}

void EarthOGL:: set_new_speed(int speed)
{
    paint_timer->setInterval(speed);
}

void EarthOGL:: mousePressEvent(QMouseEvent *pe)
{
    prs_pos = pe->pos();
}

void EarthOGL:: mouseMoveEvent(QMouseEvent *pe)
{
    x_rot += 180 * (GLfloat)(pe->y() - prs_pos.y()) / HEIGHT;
    z_rot += 180 * (GLfloat)(pe->x() - prs_pos.x()) / WIDTH;

    prs_pos = pe->pos();
    repaint();
}

void EarthOGL:: wheelEvent(QWheelEvent *pe)
{
    if ((pe->delta()) > 0 && scale < MAX_SCALE) //3e-07
      scale *= 1.1;
    else if ((pe->delta()) < 0)
      scale /= 1.1;

    repaint();
}

