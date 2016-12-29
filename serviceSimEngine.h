//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/28/2016
    Last Edited: 12/28/2016

Class Name: ServiceEngine
    Drives the processing of randomly generated customers through a number of
    service lines to be processed by cashiers
*/

#ifndef SERVICEENGINE_H
#define SERVICEENGINE_H

#include "customerParms.h"
#include "cashier.h"
#include "customerGen.h"
#include <vector>

using namespace std;


//==============================================================================
// ServiceEngine Class
//==============================================================================


class ServiceSimEngine
{

private:

// MEMBER VARIABLES ============================================================

    // Number of customers serviced and turned away
    int mNumServiced;
    int mNumTurnedAway;

    // Total wait time for all customers and the average wait time
    int mTotWaitTime;
    int mAveWaitTime;

    // Total sales and sales lost from customers turned away
    double mTotalSales;
    double mSalesLost;

    // Number of dissatisfied customers. The satisfaction is based on the wait
    // time of customer.
    int mDissatisfiedCount;

    // The number of simulations run
    int mSimulationCount;

    // The cashiers and their lines
    vector<Cashier*> mCashier;

    // The generated customer queue for entering customers
    queue<Customer*> mEnteringCustomers;

    // The customers processed
    vector<Customer*> mCustsServiced;

    // The customers turned away;
    vector<Customer*> mCustsTurnedAway;

    // The parameters for generating the customers
    CustomerParms mParameters;

public:

// CONSTRUCTORS ================================================================

    ServiceSimEngine();

    ServiceSimEngine(CustomerParms parms);

// MEMBER FUNCTIONS ============================================================


    /* Simulates the daily processing of customers through the service lines,
     * gathering various information
     *      Preconditions: LineCount, LineMax > 0;
     *      Postconditions: Customers will be sorted into two categories,
     *          serviced and turned away
     */
    void run();


//==============================================================================


    /* Print results from the service engine simulation
     *      Preconditions: None
     *      Postconditions: None
     */
    void print();


//==============================================================================


    /* Compile the data from the processed customers
     *      Preconditions: The CustsProcessed and CustsTurnedAway lists aren't
     *          empty.
     *      Postconditions: member variables will be updated with accurate info
     */
    void compileResults();

};

#endif // SERVICEENGINE_H
