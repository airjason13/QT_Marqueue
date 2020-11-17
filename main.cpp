#include "mainwindow.h"

#include <QApplication>
#include "ledscreen.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    ledscreen led;

    QObject::connect(&w,SIGNAL(stopbuttonclicked()), &led, SLOT(updateStop()));
    QObject::connect(&w,SIGNAL(startbuttonclicked(QString)), &led, SLOT(setText(QString)));

    led.show();

    w.show();
    return a.exec();
}
