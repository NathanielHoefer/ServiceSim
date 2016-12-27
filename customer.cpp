//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/27/2016
    Last Edited: 12/27/2016
*/

#include "customer.h"


//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================


Customer::Customer()
{
    mCustNum = 0;
    mEnterTime = 0;
    mServiceTime = 0;
    mPurchaseAmount = 0;
    mWaitTime = 0;
    mTurnedAway = false;
}

Customer::Customer(int custNum, int enterTime,
                   int serviceTime, double purchaseAmount)
{
    mCustNum = custNum;
    mEnterTime = enterTime;
    mServiceTime = serviceTime;
    mPurchaseAmount = purchaseAmount;
    mWaitTime = 0;
    mTurnedAway = false;
}


