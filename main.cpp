#include "mainwindow.h"

#include <QApplication>
#include <unistd.h>

std::string path=get_current_dir_name();
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    w.show();
    return a.exec();
}
