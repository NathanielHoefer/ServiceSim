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

    cout << "Using Console" << endl;

    int openTime = 8;
    int closeTime = 20;
    int custFreq = 300; // 5min
    int custFreqRange = 120; // 4-6min
    int aveServTime = 300; // 5min
    int servTimeRange = 120; // 4-6min
    double avePurchase = 5; // $5
    double purcRange = 3; // $3.50-$6.50

    CustGenParms parms = { openTime, closeTime, custFreq, custFreqRange,
                           aveServTime, servTimeRange, avePurchase, purcRange };
    CustomerGen customers(parms);

    vector<Customer*> custArr = customers.generateCustomers();

    for ( int i = 0; i < custArr.size(); i++ ) {
        custArr[i]->print();
    }

    cout << "\nService Times: " << endl;
    customers.printGraph(custArr, aveServTime, servTimeRange, 10);

    return 0;
}
