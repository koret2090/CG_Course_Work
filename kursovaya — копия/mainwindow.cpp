#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;







MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scale = SCALE;



    pen = QPen(Qt::white);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    scene->setBackgroundBrush(Qt::black);


    ui->graphicsView->installEventFilter(this);

    QLineF line(0, 0, 400, 400);
    //scene->addLine(line, pen);
    //for (double i = -400; i < 700; i++)
    //{
    //    vector<double> p = {i, i, i};
    //    draw_point(scene, pen, p);
    //}

    //draw_sphere();
    //draw_earth();

}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::draw_earth()
{
    for (int i = 0; i < earth->points_amount; i += 2)
    {
        Point point1 = earth->points[i];
        Point point2 = earth->points[i + 1];
        scene->addLine(point1.x * scale + MOVE_X, point1.y * scale + MOVE_Y,
                       point2.x * scale + MOVE_X, point2.y * scale + MOVE_Y,
                       pen);
    }
}



void MainWindow::on_up_btn_clicked()
{
    earth->turn_around_ox(ANGLE);
    scene->clear();
    draw_earth();
}

void MainWindow::on_down_btn_clicked()
{
    earth->turn_around_ox(-ANGLE);
    scene->clear();
    draw_earth();
}

void MainWindow::on_left_btn_clicked()
{
    earth->turn_around_oy(ANGLE);
    scene->clear();
    draw_earth();
}

void MainWindow::on_right_btn_clicked()
{
    earth->turn_around_oy(-ANGLE);
    scene->clear();
    draw_earth();
}

/*
void MainWindow:: wheelEvent(QWheelEvent *pe)
{
  if ((pe->delta()) > 0)
      scale *=1.1;
  else if ((pe->delta()) < 0)
      scale /= 1.1;

  scene->clear();
  draw_earth();
}
*/
bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::GraphicsSceneWheel) {
        QWheelEvent *wEvent = static_cast<QWheelEvent *>(event);

        qDebug()<<"DIIIIIOOOO";
        return true;
    } else {
        // вызов стандартного сигнала
        return QObject::eventFilter(obj, event);
    }
}
