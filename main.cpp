#include "serviceSim.h"
#include "customerGen.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ServiceSim w;
//    w.show();

//    return a.exec();

    int openTime =      11;     // 11am
    int closeTime =     22;     // 10pm
    int custFreq =      300;     // 1 min
    int custFreqMin =   30;     // 30 sec
    int custFreqMax =   600;     // 1.5 min
    int aveServTime =   300;    // 5min
    int servTimeMin =   150;    // 2.5 min
    int servTimeMax =   600;    // 10 min
    double avePurchase = 8;     // $5
    double purcMin =    2;      // $4
    double purchMax =   30;     // $30

    CustGenParms parms = { openTime, closeTime, custFreq, custFreqMin,
                           custFreqMax, aveServTime, servTimeMin, servTimeMax,
                         avePurchase, purcMin, purchMax };
    CustomerGen customers(parms);

    customers.generateCustomers();

    customers.printStats();


    cout << "\nService Times: " << endl;
//    customers.printGraph(custArr, aveServTime, servTimeRange, 5);

    return 0;
}
