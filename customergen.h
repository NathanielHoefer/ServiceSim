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

    // The hour that the store opens (military time)
    int mOpenTime;

    // The hour that the store closes (military time)
    int mCloseTime;

    // The average interval between customers entering line in seconds
    int mCustFrequency;

    // The interval in range of times in which customer enters store in seconds
    // Ex: A customer can enter anywhere between 1-5 minutes after the previous
    //      so the customer frequency range is 4 minutes so 240 seconds
    int mCustFreqRange;

    // The average service time of each customer in seconds
    int mAveServTime;

    // The interval in range of times in which customer is serviced in seconds
    // Ex: It can take anywhere from 3-6 minutes to service a customer so the
    //      service time range is 3 minutes or 180 seconds
    int mServTimeRange;

    // The average purchase of any given customer
    double mAvePurchase;

    // The interval in range of purchases between customers
    // Ex: Customers purchases range from $1-$10 so the purchase range is $9
    double mPurchaseRange;
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

public:

// CONSTRUCTORS ================================================================

    CustomerGen();

    CustomerGen(CustGenParms parms);

// MEMBER FUNCTIONS ============================================================

/* Generates the customers based on the entered parameters
 *      Preconditions: The parameters are correctly entered
 *          - 0 <= OpenTime and CloseTime <= 24
 *          - OpenTime > CloseTime
 *          - CustomerFrequency, CustFreqRange, AveServTime, ServTimeRange,
 *              AvePurchase, PurchaseRange all > 0
 *      Postconditions: A list of customers is generated
 *      Returns: A vector of customers to be entered into the Service Engine
 */
    vector<Customer*> generateCustomers();


//==============================================================================

/* Prints out a graph to the console representing the entered parameters
 *      Preconditions: Customer list has already been generated
 *      Postconditions: Graph printed to console
 */
    void printGraph(vector<Customer*> customers, int average,
                    int range, int increment);

};

#endif // CUSTOMERGEN_H
