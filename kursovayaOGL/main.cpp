#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    EarthOGL* earth = new EarthOGL();
    w.setOGL(earth);
    w.show();
    return a.exec();
}
