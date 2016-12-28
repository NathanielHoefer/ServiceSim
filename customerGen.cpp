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
    CustGenParms parms = { 0, 24, 300, 120, 300, 120, 5, 3 };
    mParameters = parms;
}


//==============================================================================


CustomerGen::CustomerGen(CustGenParms parms)
{
    mParameters = parms;
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
 *      Returns: A vector of customers to be entered into the Service Engine
 */
vector<Customer*> CustomerGen::generateCustomers()
{
    int custNum, enterTime, serviceTime, currTime;
    double purchaseAmount;
    bool isFinished = false;

    vector<Customer*> customers;
    Customer *tempCustomer;

    // Rough Standard Deviation estimates
    int custFreqStd = mParameters.mCustFreqRange / 4;
    int servTimeStd = mParameters.mServTimeRange / 4;
    double purcRangStd = round(mParameters.mPurchaseRange / 4);

    // Instanciating random generators utilizing normal ditributions
    default_random_engine enterGen(random_device{}());
    default_random_engine serviceGen(random_device{}());
    default_random_engine purchaseGen(random_device{}());
    normal_distribution<double> enterDist(mParameters.mCustFrequency,
                                          custFreqStd);
    normal_distribution<double> serviceDist(mParameters.mAveServTime,
                                            servTimeStd);
    normal_distribution<double> purchaseDist(mParameters.mAvePurchase,
                                             purcRangStd);

    // Convert to seconds
    currTime = mParameters.mOpenTime * 3600;
    custNum = 0;

    do {

        // Generates the values
        enterTime = currTime + (int)enterDist(enterGen);
        serviceTime = (int)serviceDist(serviceGen);
        purchaseAmount = purchaseDist(purchaseGen);

        // Creates the customer as long as the time doesn't exceed closing
        if ( enterTime <= (mParameters.mCloseTime * 3600) ) {
            tempCustomer = new Customer(custNum, enterTime,
                                        serviceTime, purchaseAmount);

            customers.push_back(tempCustomer);

            currTime = enterTime;
            custNum++;
        } else {
            isFinished = true;
        }

    } while ( !isFinished );

    return customers;
}


//==============================================================================


/* Prints out a graph to the console representing the entered parameters
 *      Preconditions: Customer list has already been generated
 *          state 1 = Service Time
 *          state 2 = Purchase Amount
 *      Postconditions: Graph printed to console
 */
void CustomerGen::printGraph(vector<Customer*> customers, int average,
                int range, int increment)
{
    for ( int i = (average - ( range / 2 ));
          i < (average - ( range / 2 )) + range;
          i += 10 ) {
        cout << left << i / 60 << "min ";
        cout << setfill('0') << setw(2) << i % 60 << "sec " << ": ";

        for ( int j = 0; j < customers.size(); j++ ) {
            if ( customers[j]->serviceTime() >= i &&
                 customers[j]->serviceTime() < i + increment) {
                cout << "*";
            }
        }

        cout << endl;
    }
}
