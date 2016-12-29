//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/28/2016
    Last Edited: 12/28/2016

Structure Name: CustomerParms
    Structure containing parameters for the customer generator
*/

#ifndef CUSTOMERPARMS_H
#define CUSTOMERPARMS_H

#include <vector>

using namespace std;

//==============================================================================
// CustomerParms Structure
//==============================================================================


struct CustomerParms {

    // The hours that the store opens and closes (military time)
    int mOpenTime;
    int mCloseTime;

    // The number of service lines and the max customers in a line not including
    // customers being processed by cashier
    int mNumberOfLines;
    int mMaxLineCust;

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

    // The wait time that the customer will no longer be satisfied with the
    // service
    int mDissatisfiedTime;
};

#endif // CUSTOMERPARMS_H
