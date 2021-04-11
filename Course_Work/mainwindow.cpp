#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scale = SCALE;



    pen = QPen(Qt::gray);
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene->setSceneRect(0, 0, WIDTH, HEIGHT);
    scene->setBackgroundBrush(Qt::black);

    //ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    ui->graphicsView->setEnabled(false);

    temp = 0;
    //scene->installEventFilter(this);
    //ui->graphicsView->installEventFilter(this);
    //this->installEventFilter(this);
    //ui->graphicsView->installEventFilter(this);

    QLineF line(0, 0, 400, 400);
    //scene->addLine(line, pen);
    //for (double i = -400; i < 700; i++)
    //{
    //    vector<double> p = {i, i, i};
    //    draw_point(scene, pen, p);
    //}

    //draw_sphere();
    //draw_earth();

    // создание списка траекторий
    init_trajectory_list();

}

MainWindow::~MainWindow()
{
    delete scene;
    delete ui;
}

void MainWindow::init_trajectory_list()
{
    ifstream file;
    file.open("flights.txt");

    QStringList  itemLabels;
    for (size_t i = 0; !file.eof() && i < TRAJECTORY_AMOUNT ; i++)
    {
        QString track_name;
        string city1;
        string city2;
        file >> city1 >> city2;
        QTextStream(&track_name) << QString::fromStdString(city1) << "--"
                                 << QString::fromStdString(city2);
        itemLabels << track_name;
    }

    QStringListIterator it(itemLabels);
    while (it.hasNext())
    {
          QListWidgetItem *list_item = new QListWidgetItem(it.next(),ui->trajectory_list);
          list_item->setCheckState(Qt::Unchecked);
          ui->trajectory_list->addItem(list_item);
    }
    file.close();
}

void MainWindow::draw_earth()
{
    for (size_t i = 0; i < earth->points_amount; i += 2)
    {       
        Point point1 = earth->points[i];
        Point point2 = earth->points[i + 1];
        scene->addLine(point1.x * scale + MOVE_X, point1.y * scale + MOVE_Y,
                       point2.x * scale + MOVE_X, point2.y * scale + MOVE_Y,
                       pen);
    }
}

void MainWindow::draw_trajectories()
{
    pen = QPen(Qt::green);
    pen.setWidth(2);

    for (size_t i = 0; i < earth->trajectories_amount; i++)
    {
        QListWidgetItem *item = ui->trajectory_list->item(i);
        if (item->checkState() == Qt::Checked)
        {
            for (size_t j = 0; j < earth->trajectories[i].points_amount - 1; j++)
            {
                Point point1 = earth->trajectories[i].points[j];
                Point point2 = earth->trajectories[i].points[j + 1];
                scene->addLine(-point1.x * scale + MOVE_X, -point1.y * scale + MOVE_Y,
                               -point2.x * scale + MOVE_X, -point2.y * scale + MOVE_Y,
                               pen);
            }
        }
    }
    pen = QPen(Qt::gray);
    pen.setWidth(1);
}

void MainWindow::on_up_btn_clicked()
{
    earth->turn_around_ox(ANGLE);
    scene->clear();
    draw_earth();
    draw_trajectories();
}

void MainWindow::on_down_btn_clicked()
{
    earth->turn_around_ox(-ANGLE);
    scene->clear();
    draw_earth();
    draw_trajectories();
}

void MainWindow::on_left_btn_clicked()
{
    earth->turn_around_oy(ANGLE);
    scene->clear();
    draw_earth();
    draw_trajectories();
}

void MainWindow::on_right_btn_clicked()
{
    earth->turn_around_oy(-ANGLE);
    scene->clear();
    draw_earth();
    draw_trajectories();
}

void MainWindow:: mousePressEvent(QMouseEvent *pe)
{
  prs_pos = pe->pos();
}

void MainWindow:: mouseMoveEvent(QMouseEvent *pe)
{
  x_rot = 180 * (pe->y() - prs_pos.y()) / HEIGHT;
  y_rot = 180 * (pe->x() - prs_pos.x()) / WIDTH;

  prs_pos = pe->pos();

  earth->turn_around_ox(x_rot);
  earth->turn_around_oy(y_rot);
  scene->clear();
  draw_earth();
  draw_trajectories();
}

void MainWindow:: wheelEvent(QWheelEvent *pe)
{
  if ((pe->delta()) > 0)
      scale *= 1.1;
  else if ((pe->delta()) < 0)
      scale /= 1.1;

  scene->clear();
  draw_earth();
  draw_trajectories();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event){
    if (event->type() == QEvent::GraphicsSceneWheel) {
        //QWheelEvent *wEvent = static_cast<QWheelEvent *>(event);
        temp++;
        qDebug()<<"WHEEL " << temp;
        return true;
    } else {
        // вызов стандартного сигнала
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::on_show_trajectories_btn_clicked()
{
    scene->clear();
    draw_earth();
    draw_trajectories();
}
