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

    int openTime = 11;
    int closeTime = 22;
    int custFreq = 60; // 2.5min
    int custFreqRange = 1800; // 1.5-3.5min
    int aveServTime = 30; // 5min
    int servTimeRange = 300; // 1.5-3.5min
    double avePurchase = 8; // $5
    double purcRange = 35; // $3.50-$6.50

    CustGenParms parms = { openTime, closeTime, custFreq, custFreqRange,
                           aveServTime, servTimeRange, avePurchase, purcRange };
    CustomerGen customers(parms);

    vector<Customer*> custArr = customers.generateCustomers();

    cout << left << setw(6) << "Cust" << setw(12) << "Enter Time" <<
            setw(15) << "Service Time" << setw(10) << "Amount" << endl;

    cout << left << setw(6) << "----" << setw(12) << "----------" <<
            setw(15) << "-------------" << setw(10) << "----------" << endl;

    for ( int i = 0; i < custArr.size(); i++ ) {
        custArr[i]->print();
    }

    cout << "\nService Times: " << endl;
//    customers.printGraph(custArr, aveServTime, servTimeRange, 5);

    return 0;
}
