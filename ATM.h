// final version
//
//  ATM.h
//  ATM
//
#ifndef main_h
#define main_h
#include "Customer.h"
#include <vector>
using namespace std;



class ATM {
    friend class Customer;
private:
    //need to initialize allCustomers
    vector<Customer> allCustomers = {Customer("x","x","x",1,5,1),Customer("y","y","y",2,6,2)};
    int findCustomer(int cardNumber){
        //iterates through allCustomers comparing cardNumbers until it finds a match
        for (int i = 0; i < allCustomers.size(); i++) {
            if (allCustomers[i].compareCardNumber(cardNumber)){
                return i;
            }
        }
        
        //returns -1 if no match is found
        return -1;
    }
    
public:
    Customer currentCustomer = Customer("","","",0,0,0);
    
    bool addNewCustomer();
    
    //finish method below
    bool setCurrentCustomer(int cardNumber){
        //makes sure cardNumber is that of valid Customer
        int x = findCustomer(cardNumber);
        if (x < 0) {
            return false;
        }
        cout << "Please enter your PIN";
        int PIN;
        
        //need guards for cin
        cin >> PIN;
        //add possible loops for missed trys
        //checks that user knows PIN for cardNumber
        if (allCustomers[x].comparePIN(PIN)){
            currentCustomer = allCustomers[x];
            return true;
        }
        
        return false;
    }
    
    Customer getCustomer(int cardNumber){
        int x = findCustomer(cardNumber);
        
        //if x is within the size of allCustomers returns the customer at that location
        if (x > -1) {
            return allCustomers[x];
        }
        
        //otherwise returns nullptr reference (NULL)
        return Customer("","","",0,0,0);
    }
    
    bool transfer(int cardNumber, double x){
        Customer transferTo = getCustomer(cardNumber);
        
        //attempts to make withdrawal, if there are sufficient funds, makes deposit in other account, returns true
        if (!transferTo.compareTo(Customer("","","",0,0,0)) && currentCustomer.makeWithdrawal(x)){
            transferTo.makeDeposit(x);
            return true;
        }
        
        //customer is unable to transfer the funds, returns false
        cout << "Unable to transfer funds." << endl;
        return false;
    }
    
};



#endif /* main_h */
