//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/28/2016
    Last Edited: 12/28/2016
*/

#include "cashier.h"


//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================


Cashier::Cashier()
{
    mProcessTime = 0;
    mAvailable = true;
}


//==============================================================================
// MEMBER FUNCTIONS
//==============================================================================


/* Adds a customer to the cashier's service line
 *      Preconditions: None
 *      Postconditions: Customer is queued
 */
void Cashier::addCustomer(Customer *customer)
{
    mServiceLine.push(customer);
}


//==============================================================================


/* Retrieves the next customer in line and removes from queue
 *      Preconditions: Line isn't empty
 *      Postconditions: Customer removed from queue
 *      Returns: Pointer of front customer
 */
Customer* Cashier::nextCustomer()
{
    Customer* customer = mServiceLine.front();
    mServiceLine.pop();
    return customer;
}
