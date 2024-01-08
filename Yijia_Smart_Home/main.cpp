#include "main_interface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Main_interface w;
    w.show();

    return a.exec();
}
