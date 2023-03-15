#include "mainwindow.h"
#include <Test.h>


#include <QApplication>

int main(int argc, char *argv[])
{
    Test();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
