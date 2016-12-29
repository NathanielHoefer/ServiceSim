//==============================================================================
// Service Simulator Project
//==============================================================================
/*  Author: Nathaniel Hoefer
    Date Created: 12/28/2016
    Last Edited: 12/28/2016
*/

#include "serviceSimEngine.h"


//==============================================================================
// CONSTRUCTORS / DESTRUCTORS
//==============================================================================


ServiceSimEngine::ServiceSimEngine()
{
    vector<Cashier*> temp(1);
    mCashier = temp;

    mNumServiced = 0;
    mNumTurnedAway = 0;

    mTotWaitTime = 0;
    mAveWaitTime = 0;

    mTotalSales = 0;
    mSalesLost = 0;

    mDissatisfiedCount = 0;
    mSimulationCount = 0;
}


//==============================================================================


ServiceSimEngine::ServiceSimEngine(CustomerParms parms)
{
    for ( int i = 0; i < parms.mNumberOfLines; i++ ) {
        Cashier *temp = new Cashier();
        mCashier.push_back(temp);
    }

    mParameters = parms;

    mNumServiced = 0;
    mNumTurnedAway = 0;

    mTotWaitTime = 0;
    mAveWaitTime = 0;

    mTotalSales = 0;
    mSalesLost = 0;

    mDissatisfiedCount = 0;
    mSimulationCount = 0;
}


//==============================================================================
// MEMBER FUNCTIONS
//==============================================================================


/* Simulates the daily processing of customers through the service lines,
 * gathering various information
 *      Preconditions: LineCount, LineMax > 0;
 *      Postconditions: Customers will be sorted into two categories,
 *          serviced and turned away
 */
void ServiceSimEngine::run()
{
    clock_t tStart = clock();

    CustomerGen custGenerator(mParameters);
    mEnteringCustomers = custGenerator.generateCustomers();
    custGenerator.printStats();

//    cout << mCashier.size() << endl;

//    Customer cust1(0, 0, 5, 5);
//    Customer cust2(0, 1, 5, 5);
//    Customer cust3(0, 2, 3, 5);

//    mEnteringCustomers.push(&cust1);
//    mEnteringCustomers.push(&cust2);
//    mEnteringCustomers.push(&cust3);

    int currentTime, openTime, closeTime;
    openTime = mParameters.mOpenTime * 3600;
//    closeTime = 10;
    closeTime = mParameters.mCloseTime * 3600;

    // Loop that processes every second of the workday
    for ( currentTime = openTime; currentTime < closeTime; currentTime++ ) {

        // Check cashier service time
        for ( int i = 0; i < mParameters.mNumberOfLines; i++ ) {
            Cashier *cashier = mCashier[i];

            // Reduce current process time when cashier is with customer
            if ( !cashier->isAvailable() ) {
                cashier->decProcessTime();
            }

            if ( cashier->processTime() == 0 ) {
                cashier->setAvailable(true);
            }
        }


        // Replace customer when cashier is available
        for ( int i = 0; i < mParameters.mNumberOfLines; i++ ) {
            Cashier *cashier = mCashier[i];

            if ( cashier->lineSize() > 0 && cashier->isAvailable() ) {
                Customer* customer = cashier->nextCustomer();

                int waitTime = currentTime - customer->enterTime();
                customer->setWaitTime(waitTime);
                customer->setTurnedAway(false);

                cashier->setProcessTime(customer->serviceTime());

                mCustsServiced.push_back(customer);
            }
        }


        // Add next customer to a service line
        if ( !mEnteringCustomers.empty() ) {
            Customer *customer = mEnteringCustomers.front();
            if ( customer->enterTime() == currentTime ) {
                mEnteringCustomers.pop();

                Cashier *cashier;
                bool lineFound = false;
                vector<int> lineCount(mParameters.mNumberOfLines);

                for ( int i = 0; i < mParameters.mNumberOfLines; i++ ) {
                    cashier = mCashier[i];

                    // Go to first line available
                    if ( cashier->isAvailable() ) {
                        int waitTime = currentTime - customer->enterTime();
                        customer->setWaitTime(waitTime);
                        customer->setTurnedAway(false);

                        cashier->setProcessTime(customer->serviceTime());
                        cashier->setAvailable(false);

                        mCustsServiced.push_back(customer);

                        i = mParameters.mNumberOfLines;
                        lineFound = true;
                    } else {
                        lineCount[i] = cashier->lineSize();
                    }
                }

                // Find the smallest line
                if ( !lineFound ) {
                    Cashier *smallestLine = mCashier[0];
                    int smallLineSize = mCashier[0]->lineSize();

                    for ( int i = 1; i < mParameters.mNumberOfLines; i++ ) {
                        if ( mCashier[i]->lineSize() < smallestLine->lineSize() ) {
                            smallestLine = mCashier[i];
                            smallLineSize = mCashier[i]->lineSize();
                        }
                    }

                    if ( smallLineSize < mParameters.mMaxLineCust ) {
                        smallestLine->addCustomer(customer);
                    } else {
                        // Customer is turned away because all lines are full
                        customer->setTurnedAway(true);
                        mCustsTurnedAway.push_back(customer);
                    }
                }
            }
        }
    }

    compileResults();
    print();

    cout << "\nTime taken: " << fixed << setprecision(3) <<
            (double)(clock() - tStart)/CLOCKS_PER_SEC << " seconds" << endl;
}


//==============================================================================


/* Print results from the service engine simulation
 *      Preconditions: None
 *      Postconditions: None
 */
void ServiceSimEngine::print() {

    cout << "===========================================" << endl;
    cout << "Simulation Results" << endl;
    cout << "===========================================\n" << endl;

    cout << left << setw(25) << "Customers Serviced: " <<
            mNumServiced << endl;
    cout << setw(25) << "Customers Turned Away: " <<
            mNumTurnedAway << endl << endl;

    cout << setw(25) << "Total Sales Amount: " <<
            fixed << setprecision(2) << "$ " << mTotalSales << endl;
    cout << setw(25) << "Total Sales Lost: " <<
            fixed << setprecision(2) << "$ " << mSalesLost << endl << endl;

    cout << setw(25) << "Total Wait Time: " <<
            mTotWaitTime / 60 << " min " <<
            mTotWaitTime % 60 << " sec " << endl;
    cout << setw(25) << "Average Wait Time: " <<
            mAveWaitTime / 60 << " min " <<
            mAveWaitTime % 60 << " sec " << endl << endl;

    cout << setw(25) << "Dissatisfied Customers: " <<
            mDissatisfiedCount << endl;
}


//==============================================================================


/* Compile the data from the processed customers
 *      Preconditions: The CustsProcessed and CustsTurnedAway lists aren't
 *          empty.
 *      Postconditions: member variables will be updated with accurate info
 */
void ServiceSimEngine::compileResults()
{
    mNumServiced += (int)mCustsServiced.size();
    mNumTurnedAway += (int)mCustsTurnedAway.size();

    for ( int i = 0; i < mCustsServiced.size(); i++ ) {
        mTotWaitTime += mCustsServiced[i]->waitTime();
        mTotalSales += mCustsServiced[i]->purchaseAmount();

        if ( mCustsServiced[i]->waitTime() >= mParameters.mDissatisfiedTime ) {
            mDissatisfiedCount++;
        }
    }

    mAveWaitTime = mTotWaitTime / mNumServiced;

    for ( int i = 0; i < mCustsTurnedAway.size(); i++ ) {
        mSalesLost += mCustsTurnedAway[i]->purchaseAmount();
    }

    mDissatisfiedCount += (int)mCustsTurnedAway.size();
}
