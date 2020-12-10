#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "earthogl.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setOGL(EarthOGL* planet) {earth = planet;}
    void init_trajectory_list();

private slots:
    void on_show_trajectories_btn_clicked();

    void on_verticalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    EarthOGL* earth;



};
#endif // MAINWINDOW_H
