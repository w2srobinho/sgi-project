#include "mainwindow.h"
#include <QApplication>
#include "gui_resources.h"

int main(int argc, char *argv[])
{
    gui_resources::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
