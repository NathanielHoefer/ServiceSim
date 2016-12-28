#include "driverTesting.h"
#include <time.h>

using namespace std;

Driver::Driver() {

}

void Driver::custGenTesting()
{
    clock_t tStart = clock();

    // Approximate Bogey's Times for reference
    int openTime =      11;     // 11am
    int closeTime =     22;     // 10pm

    int custFreq =      600;     // 10 min
    int custFreqMin =   180;     // 3 min
    int custFreqMax =   1800;    // 30 min

    vector<int> busyHours;      // Busy hours: 12-1, 5-6
    busyHours.push_back(12);
    busyHours.push_back(13);
    busyHours.push_back(17);
    busyHours.push_back(18);

    int custBFreq =     120;    // 1 min
    int custBFreqMin =  30;     // 30 sec
    int custBFreqMax =  300;    // 2 min

    int aveServTime =   300;    // 5min
    int servTimeMin =   150;    // 2.5 min
    int servTimeMax =   600;    // 10 min

    double avePurchase = 8;     // $5
    double purcMin =    2;      // $4
    double purchMax =   30;     // $30

    CustGenParms parms = { openTime, closeTime, busyHours,
                           custFreq, custFreqMin, custFreqMax,
                           custBFreq, custBFreqMin, custBFreqMax,
                           aveServTime, servTimeMin, servTimeMax,
                           avePurchase, purcMin, purchMax };

    CustomerGen customers(parms);

    customers.generateCustomers();

    customers.printStats();

    cout << "\nTime taken: " << fixed << setprecision(3) <<
            (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
}
