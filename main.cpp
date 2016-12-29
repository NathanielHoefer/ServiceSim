#include "serviceSim.h"
#include "driverTesting.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ServiceSim w;
//    w.show();

//    return a.exec();

    Driver testing;

    testing.serviceSimEngineTesting();

    return 0;
}
