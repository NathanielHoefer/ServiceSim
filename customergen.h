//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/27/2016
    Last Edited: 12/27/2016

Structure Name: CustGenParms
    Structure containing parameters for the customer generator

Class Name: CustomerGen
    Generates a random list of customers based on specified parameters that will
    be fed into the ServiceEngine

*/

#ifndef CUSTOMERGEN_H
#define CUSTOMERGEN_H

#include "customer.h"
#include <vector>

using namespace std;


//==============================================================================
// CustGenParms Structure
//==============================================================================


struct CustGenParms {

    // The hours that the store opens and closes (military time)
    int mOpenTime;
    int mCloseTime;

    // The hours that are busy
    vector<int> mBusyHours;

    // The average, minimum and maximum intervals between customers entering
    // line in seconds
    int mCustFrequency;
    int mCustFreqMin;
    int mCustFreqMax;

    // The average, minimum and maximum intervals between customers entering
    // line during busy part of day
    int mBCustFrequency;
    int mBCustFreqMin;
    int mBCustFreqMax;

    // The average, minimum and maximum service time of each customer in seconds
    int mAveServTime;
    int mServTimeMin;
    int mServTimeMax;

    // The average, minimum and maximum purchase of any given customer
    double mAvePurchase;
    double mPurchaseMin;
    double mPurchaseMax;
};


//==============================================================================
// CustmerGen Class
//==============================================================================


class CustomerGen
{

private:

// MEMBER VARIABLES ============================================================

    // The parameters for generating the customers
    CustGenParms mParameters;

    // Most current generated customers
    vector<Customer*> mGenCustomers;

    /* Most current generated statistics of the 3 generated data. The stats are
     * listed as columns to be printed out as a *-graph
     *  [0] = Enter Times
     *  [1] = Service Times
     *  [2] = Purchase Amounts
     */
    vector < vector<int> > mStats;

    // The number of generations performed
    int mGenCount;

public:

// CONSTRUCTORS ================================================================

    CustomerGen();

    CustomerGen(CustGenParms parms);

    ~CustomerGen();

// MEMBER FUNCTIONS ============================================================


/* Generates the customers based on the entered parameters
 *      Preconditions: The parameters are correctly entered
 *          - 0 <= OpenTime and CloseTime <= 24
 *          - OpenTime > CloseTime
 *          - CustFreqMin < CustFrequency < CustFreqMax
 *          - ServTimeMin < AveServTime < ServTimeMax
 *          - PurchaseMin < avePurchase < PurchaseMax
 *      Postconditions: A list of customers is generated
 *      Returns: A vector of customers to be entered into the Service Engine
 */
    const vector<Customer*> generateCustomers();


//==============================================================================


/* Prints out the statistics of the generated customers for better visualization
 * of the data.
 *      Preconditions: None
 *      Postconditions: Statistics are printed
 */
    void printStats();


//==============================================================================

private:

/* Adds the element value to the specified graph for later statistics
 *      Preconditions: Entered value is between min and max, index is 0-2
 *      Postconditions: None
 */
    void addGraphElem(int index, double value);

};

#endif // CUSTOMERGEN_H
