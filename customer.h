//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/27/2016
    Last Edited: 12/27/2016

Class Name: Customer
    This class contains the information needed for each customer that is to be
    processed by the ServiceEngine

*/

#ifndef CUSTOMER_H
#define CUSTOMER_H

using namespace std;


//==============================================================================
// CUSTOMER CLASS
//==============================================================================


class Customer
{

private:

// MEMBER VARIABLES ============================================================

    // The order in which the customer enters
    int mCustNum;

    // The minute that the customer enters the store
    int mEnterTime;

    // The time taken for the cashier to service the customer
    int mServiceTime;

    // The amount of items the customer purchased
    double mPurchaseAmount;

    // The time waiting in line to be processed.
    int mWaitTime;

    // Customer is turned away or not
    bool mTurnedAway;

public:

// CONSTRUCTORS ================================================================

    Customer();

    Customer(int custNum, int enterTime,
             int serviceTime, double purchaseAmount);

// ACCESSORS / MUTATORS ========================================================

    int custNum() const { return mCustNum; }
    int enterTime() const { return mEnterTime; }
    int serviceTime() const { return mServiceTime; }
    double purchaseAmount() const { return mPurchaseAmount; }
    int waitTime() const { return mWaitTime; }
    bool turnedAway() const { return mTurnedAway; }

    void setCustNum( int custNum ) { mCustNum = custNum; }
    void setEnterTime( int enterTime ) { mEnterTime = enterTime; }
    void setServiceTime( int serviceTime ) { mServiceTime = serviceTime; }
    void setPurchaseAmount( double amount ) { mPurchaseAmount = amount; }
    void setWaitTime( int waitTime ) { mWaitTime = waitTime; }
    void setTurnedAway( bool turnedAway ) { mTurnedAway = turnedAway; }
};

#endif // CUSTOMER_H
