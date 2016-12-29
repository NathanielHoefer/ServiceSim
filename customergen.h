//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/27/2016
    Last Edited: 12/27/2016

Class Name: CustomerGen
    Generates a random list of customers based on specified parameters that will
    be fed into the ServiceEngine

*/

#ifndef CUSTOMERGEN_H
#define CUSTOMERGEN_H

#include "customerParms.h"
#include "customer.h"
#include <vector>
#include <queue>

using namespace std;


//==============================================================================
// CustmerGen Class
//==============================================================================


class CustomerGen
{

private:

// MEMBER VARIABLES ============================================================

    // The parameters for generating the customers
    CustomerParms mParameters;

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

    CustomerGen(CustomerParms parms);

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
    queue<Customer*> generateCustomers();


//==============================================================================


/* Resets the state of the customer generator leaving the parameters and
 *  generation count
 *      Preconditions: None
 *      Postconditions: Customers and statistics are erased
 */
    void reset();


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
