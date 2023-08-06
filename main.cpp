#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    global_config_init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int ret = a.exec();

    global_config_exit();
    return ret;
}
