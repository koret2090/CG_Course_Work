#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Earth earth = Earth();
    MainWindow w;
    w.set_earth(&earth);
    w.draw_earth();
    w.show();
    return a.exec();
}
