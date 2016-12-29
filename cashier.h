//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/28/2016
    Last Edited: 12/28/2016

Class Name: Customer
    This class contains the service lines for customers to be processed
*/

#ifndef CASHIER_H
#define CASHIER_H

#include <customer.h>
#include <queue>

using namespace std;


//==============================================================================
// Cashier Class
//==============================================================================


class Cashier
{

private:

// MEMBER VARIABLES ============================================================

    // The service line for waiting customers before being processed
    queue<Customer*> mServiceLine;

    // The time remaining to process the current customer
    int mProcessTime;

    // Shows whether the cashier is available to process another customer
    bool mAvailable;

public:

// CONSTRUCTORS ================================================================

    Cashier();

// ACCESSORS / MUTATORS ========================================================

    int lineSize() const { return (int)mServiceLine.size(); }
    int processTime() const { return mProcessTime; }
    bool isAvailable() const { return mAvailable; }

    void setProcessTime(int processTime) { mProcessTime = processTime; }
    void setAvailable(bool avail) { mAvailable = avail; }

// MEMBER FUNCTIONS ============================================================


    /* Adds a customer to the cashier's service line
     *      Preconditions: None
     *      Postconditions: Customer is queued
     */
    void addCustomer(Customer *customer);


//==============================================================================


    /* Decrements the process time for the cashier
     *      Preconditions: Cashier must not be available
     *      Postconditions: Process time is reduced by 1
     */
    void decProcessTime() { mProcessTime--; }


//==============================================================================


    /* Retrieves the next customer in line and removes from queue
     *      Preconditions: Line isn't empty
     *      Postconditions: Customer removed from queue
     *      Returns: Pointer of front customer
     */
    Customer* nextCustomer();

};

#endif // CASHIER_H
