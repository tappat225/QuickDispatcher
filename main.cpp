#include "mainwindow.h"
// #include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // QPushButton button ("Hello world !");
    // button.show();
    return a.exec();
}
