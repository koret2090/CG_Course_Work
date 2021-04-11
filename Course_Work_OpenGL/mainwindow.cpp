#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(WINDOW_W, WINDOW_H);
    ui->setupUi(this);
    init_trajectory_list();
}

MainWindow::~MainWindow()
{
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
        string city1, city2;
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

void MainWindow::on_show_trajectories_btn_clicked()
{
    for (size_t i = 0; i < ui->scene->trajectories_amount; i++)
    {
        QListWidgetItem *item = ui->trajectory_list->item(i);
        if (item->checkState() == Qt::Checked)
            ui->scene->trajectories[i].set_selection(true);
        else
            ui->scene->trajectories[i].set_selection(false);
    }
    ui->scene->repaint();
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
   ui->scene->set_new_speed(START_FLIGHT_SPEED - value);
   ui->scene->repaint();
}
