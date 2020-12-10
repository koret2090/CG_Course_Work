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

private:
    Ui::MainWindow *ui;
    EarthOGL* earth;



};
#endif // MAINWINDOW_H
