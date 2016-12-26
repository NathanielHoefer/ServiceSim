#include "servicesim.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ServiceSim w;
    w.show();

    return a.exec();
}
