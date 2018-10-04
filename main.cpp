#include "mainwindow.hpp"
#include <QApplication>
#include<alize/alize.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    alize::Config dis;
    std::cout << dis.existsParam("dupa");


    return a.exec();
}
