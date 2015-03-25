#include "mainwindow.h"
#include <QApplication>
#include "gui_resources.h"

int main(int argc, char *argv[])
{

    //Q_INIT_RESOURCE(ClientMainWindowViewQt);
    gui_resources::Init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
