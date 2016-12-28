//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/27/2016
    Last Edited: 12/27/2016
*/

#include "customerGen.h"
#include <random>
#include <cmath>

using namespace std;


//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================


CustomerGen::CustomerGen()
{
    vector<int> busyHours;      // Busy hours: 12-1, 5-6
    busyHours.push_back(12);
    busyHours.push_back(13);
    busyHours.push_back(17);
    busyHours.push_back(18);

    CustGenParms parms = { 11, 22, busyHours, 600, 180, 1800,
                           60, 30, 120, 300, 150, 600, 8, 2, 30 };
    mParameters = parms;
    vector< vector<int> > temp(3, vector<int>(10, 0));
    mStats = temp;
    mGenCount = 0;
}


//==============================================================================


CustomerGen::CustomerGen(CustGenParms parms)
{
    mParameters = parms;

    vector<int> custFreqTemp((parms.mCloseTime - parms.mOpenTime), 0);
    vector<int> servTimeTemp(10, 0);
    vector<int> purchTimeTemp(10, 0);

    mStats.push_back(custFreqTemp);
    mStats.push_back(servTimeTemp);
    mStats.push_back(purchTimeTemp);

    mGenCount = 0;
}


//==============================================================================


CustomerGen::~CustomerGen()
{
    for ( int i = 0; i < mGenCustomers.size(); i++ ) {
        delete mGenCustomers[i];
    }
}

//==============================================================================
// MEMBER FUNCTIONS
//==============================================================================


/* Generates the customers based on the entered parameters
 *      Preconditions: The parameters are correctly entered
 *          - 0 <= OpenTime and CloseTime <= 24
 *          - OpenTime > CloseTime
 *          - CustomerFrequency, CustFreqRange, AveServTime, ServTimeRange,
 *              AvePurchase, PurchaseRange all > 0
 *      Postconditions: A list of customers is generated
 */
const vector<Customer*> CustomerGen::generateCustomers()
{
    // Clear previous generation
    if ( mGenCustomers.size() > 0 ) {
        mGenCustomers.clear();
    }

// Customer Frequency Generator
    int custFreq, custFreqMin, custFreqMax;
    custFreq = mParameters.mCustFrequency;
    custFreqMin = mParameters.mCustFreqMin;
    custFreqMax = mParameters.mCustFreqMax;

    int custBusyFreq, custBusyFreqMin, custBusyFreqMax;
    custBusyFreq = mParameters.mBCustFrequency;
    custBusyFreqMin = mParameters.mBCustFreqMin;
    custBusyFreqMax = mParameters.mBCustFreqMax;

    int custFreqStd = (custFreqMax - custFreqMin) / 4;
    int custBusyFreqStd = (custBusyFreqMax - custBusyFreqMin) / 4;

    default_random_engine enterGen(random_device{}());
    normal_distribution<double> enterDist(custFreq, custFreqStd);
    normal_distribution<double> enterBusyDist(custBusyFreq, custBusyFreqStd);


// Service Time Generator
    int aveServTime, servTimeMin, servTimeMax;
    aveServTime = mParameters.mAveServTime;
    servTimeMin = mParameters.mServTimeMin;
    servTimeMax = mParameters.mServTimeMax;

    int servTimeStd = (servTimeMax - servTimeMin) / 4;

    default_random_engine serviceGen(random_device{}());
    normal_distribution<double> serviceDist(aveServTime, servTimeStd);


// Purchase Amount Generator
    double avePurchase, purchaseMin, purchaseMax;
    avePurchase = mParameters.mAvePurchase;
    purchaseMin = mParameters.mPurchaseMin;
    purchaseMax = mParameters.mPurchaseMax;

    double purcRangStd = round((purchaseMax - purchaseMin) / 4);

    default_random_engine purchaseGen(random_device{}());
    normal_distribution<double> purchaseDist(avePurchase, purcRangStd);


    // Declaring generation variables
    int custNum, enterTime, serviceTime, currTime;
    double purchaseAmount;
    bool isFinished = false;

    Customer *tempCustomer;
    bool busyHour;

    // Convert to seconds
    currTime = mParameters.mOpenTime * 3600;
    custNum = 0;


// Customer Generation
    do {

// Customer Frequency Generation

        // If current time is designated busy hour, set flag
        for ( int i = 0; i < mParameters.mBusyHours.size(); i++ ) {
            if ( currTime / 3600 == mParameters.mBusyHours[i] ) {
                busyHour = true;
                i = 25;
            } else {
                busyHour = false;
            }
        }

        // Use busy distribution if busy hour
        if ( busyHour ) {
            do {
                enterTime = (int)enterBusyDist(enterGen);
            } while ( enterTime < custBusyFreqMin ||
                      enterTime > custBusyFreqMax );
        } else {
            do {
                enterTime = (int)enterDist(enterGen);
            } while ( enterTime < custFreqMin ||
                      enterTime > custFreqMax );
        }
        enterTime += currTime;
        addGraphElem(0, (double)enterTime);

        // Service Time Generation
        do {
            serviceTime = (int)serviceDist(serviceGen);
        } while ( serviceTime < servTimeMin ||
                  serviceTime > servTimeMax );
        addGraphElem(1, (double)serviceTime);

        // Purchase Amount Generation
        do {
            purchaseAmount = purchaseDist(purchaseGen);
        } while ( purchaseAmount < purchaseMin ||
                  purchaseAmount > purchaseMax );
        addGraphElem(2, purchaseAmount);


        // Creates the customer as long as the time doesn't exceed closing
        if ( enterTime <= (mParameters.mCloseTime * 3600) ) {
            tempCustomer = new Customer(custNum, enterTime,
                                        serviceTime, purchaseAmount);

            mGenCustomers.push_back(tempCustomer);

            currTime = enterTime;
            custNum++;
        } else {
            isFinished = true;
        }

        mGenCount++;

    } while ( !isFinished );

    return mGenCustomers;
}


//==============================================================================


/* Prints out the statistics of the generated customers for better visualization
 * of the data.
 *      Preconditions: None
 *      Postconditions: Statistics are printed
 */
void CustomerGen::printStats() {

    cout << "===========================================" << endl;
    cout << "Customer Generation Statistics" << endl;
    cout << "===========================================\n" << endl;

    // Print customer info labels
    cout << left << setw(6) << "Cust" << setw(12) << "Enter Time" <<
            setw(15) << "Service Time" << setw(10) << "Amount" << endl;

    cout << left << setw(6) << "----" << setw(12) << "----------" <<
            setw(15) << "-------------" << setw(10) << "----------" << endl;

    // Format and print out individual customer info
    for ( int i = 0; i < mGenCustomers.size(); i++ ) {
        int custNum = mGenCustomers[i]->custNum();
        int enterTime = mGenCustomers[i]->enterTime();
        int serviceTime = mGenCustomers[i]->serviceTime();
        double purchaseAmount = mGenCustomers[i]->purchaseAmount();

        cout << left << setfill(' ') << setw(6) << custNum;

        cout << right << setfill('0') << setw(2) << enterTime / 3600 << ":";
        enterTime = enterTime % 3600;
        cout << setfill('0') << setw(2) << enterTime / 60 << ":";
        enterTime = enterTime % 60;
        cout << setfill('0') << setw(2) << enterTime << "    ";

        cout << serviceTime / 60 << " min ";
        cout << setfill('0') << setw(2) << serviceTime % 60 <<
             left << setfill(' ') << setw(7) << " sec";

        cout << "$" << setprecision(2) << fixed <<
                setw(2) << purchaseAmount << endl;
    }


    // Print the three graphs
    for ( int i = 0; i < 3; i++ ) {

        int graphIndex = 0;
        int increment;
        switch (i) {
        case 0:
            cout << "\nCustomers During Workday" << endl;
            cout << "------------------------" << endl;

            int openTime, closeTime;
            openTime = mParameters.mOpenTime;
            closeTime = mParameters.mCloseTime;
            increment = 1;

            for ( int j = openTime; j < closeTime; j += increment ) {

                if ( j <= 12 ) {
                    cout << right << setw(2) << j << " am : ";
                } else {
                    cout << right << setw(2) << j % 12 << " pm : ";
                }
                for ( int k = 0; k < mStats[i][graphIndex]; k++ ) {
                    cout << "*";
                }
                cout << endl;
                graphIndex++;
            }

            graphIndex = 0;
            break;
        case 1:
            cout << "\nService Times" << endl;
            cout << "------------------------" << endl;

            int servTimeMin, servTimeMax;
            servTimeMin = mParameters.mServTimeMin;
            servTimeMax = mParameters.mServTimeMax;
            increment = (servTimeMax - servTimeMin) / 10;

            for ( int j = servTimeMin; j < servTimeMax; j += increment ) {

                cout << left << j / 60 << "min ";
                cout << right << setfill('0') << setw(2) <<
                        j % 60 << "sec " << ": ";
                for ( int k = 0; k < mStats[i][graphIndex]; k++ ) {
                    cout << "*";
                }
                cout << endl;
                graphIndex++;
            }

            graphIndex = 0;
            break;
        case 2:
            cout << "\nPurchase Amounts" << endl;
            cout << "------------------------" << endl;

            double purchMin, purchMax;
            purchMin = mParameters.mPurchaseMin;
            purchMax = mParameters.mPurchaseMax;

            double doubInc = (purchMax - purchMin) / 10;

            for ( double j = purchMin; j < purchMax; j += doubInc ) {

                cout << left << fixed << setfill(' ') << setprecision(2) <<
                        "$ " << setw(6) << j << " : ";
                for ( int k = 0; k < mStats[i][graphIndex]; k++ ) {
                    cout << "*";
                }
                cout << endl;
                graphIndex++;
            }
            break;
        }
    }
}


//==============================================================================


/* Adds the element value to the specified graph for later statistics
 *      Preconditions: Entered value is between min and max, index is 0-2
 *      Postconditions: None
 */
void CustomerGen::addGraphElem(int index, double value)
{
    int increment, graphIndex;

    switch (index) {

    // Enter Times
    case 0:
        int openTime, closeTime;
        openTime = mParameters.mOpenTime;
        closeTime = mParameters.mCloseTime;
        increment = 1;
        graphIndex = 0;
        value /= 3600;

        for ( int i = openTime; i < closeTime; i += increment ) {
            if ( value >= i && value < i + increment ) {
                mStats[index][graphIndex]++;
                i = closeTime;
            }
            graphIndex++;
        }
        break;

    // Service Times
    case 1:
        int servTimeMin, servTimeMax;
        servTimeMin = mParameters.mServTimeMin;
        servTimeMax = mParameters.mServTimeMax;

        increment = (servTimeMax - servTimeMin) / 10;
        graphIndex = 0;

        for ( int i = servTimeMin; i < servTimeMax; i += increment ) {
            if ( value >= i && value < i + increment ) {
                mStats[index][graphIndex]++;
                i = servTimeMax;
            }
            graphIndex++;
        }
        break;

    // Purchase Amounts
    case 2:
        double purchMin, purchMax;
        purchMin = mParameters.mPurchaseMin;
        purchMax = mParameters.mPurchaseMax;

        double doubInc = (purchMax - purchMin) / 10;
        graphIndex = 0;

        for ( double i = purchMin; i < purchMax; i += doubInc ) {
            if ( value >= i && value < i + doubInc ) {
                mStats[index][graphIndex]++;
                i = purchMax;
            }
            graphIndex++;
        }
        break;
    }
}
