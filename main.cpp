#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //MainWindow r;
    w.resize(1000, 600);
    //r.show();
    w.X();
    w.show();

    return a.exec();
}
