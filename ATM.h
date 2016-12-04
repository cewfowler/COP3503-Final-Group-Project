//
//  main.h
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
    vector<Customer> allCustomers;
    Customer currentCustomer();
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
        x = findCustomer(cardNumber);
        
        //if x is within the size of allCustomers returns the customer at that location
        if (x > -1) {
            return allCustomers[x];
        }
        
        //otherwise returns nullptr reference (NULL)
        return nullptr;
    }
    
};



#endif /* main_h */
