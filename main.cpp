#include "mainwindow.h"
#include <QApplication>
#include "HH.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
	setHook(&w);
    return a.exec();
}
