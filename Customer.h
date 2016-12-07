//Kenny Ramos
//Harrison Schorr
//Gianfranco Dutka
//Cyrus Najmi
//Eric Roque
//Christian Fowler
//Brooke Mott-Smith

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
    vector<Customer> allCustomers = {};
    
    int findCustomer(long cardNumber){
        //iterates through allCustomers comparing cardNumbers until it finds a match
        for (int i = cardNumber % 10; i < allCustomers.size(); i += 10) {
            if (allCustomers[i].getCardNumber() == cardNumber){
                return i;
            }
        }
        
        //returns -1 if no match is found
        
        cout<<"Customer not found, try again\n";
        return -1;
    }
    
public:
    int currentCustomer = -1;
    
    bool transfer(long cardNumber, double x){
        int i = findCustomer(cardNumber);
        
        //attempts to make withdrawal, if there are sufficient funds, makes deposit in other account, returns true
        if (i > -1 && allCustomers[currentCustomer].makeWithdrawal(x)){
            allCustomers[i].makeDeposit(x);
            
            //allCustomers[i].getBalance();
            
            return true;
        }
        
        //customer is unable to transfer the funds, returns false
        cout << "Unable to transfer funds." << endl;
        return false;
    }
    
    int cardLastDigit=0;
    
    void displayMenu(){
        int choice=0;
        bool continuing = true;
        long cardNumber=0;
        while (continuing){
            cout<< "Welcome!\nAre you an existing or new user?\nEnter:\n1 For Existing Customer \n2 For New Customer\n"<<endl;
            choice = userInputNumber();
        
            int userFound = -1;

            switch(choice){
                case 1:
                

                    cout<<"Enter your card number: ";
                    cin>>cardNumber;
                    userFound=findCustomer(cardNumber);
                    
                    if (userFound == -1){
                        cout << "Unable to find user."<< endl;
                        break;
                    }
                
                    
                    if (setCurrentCustomer(cardNumber, false)){
                        cout<<"\nSuccessfully signed in!\n"<<endl;
                    
                    }
                    else {
                        cout << "Unable to sign in. "<< endl;
                        break;
                    }
                    continuing = false;
                    break;
                
                case 2:
                    addNewCustomer();

                    cout<<"\nAccount Successfully Created!!!\n\n";
                    continuing = false;
                    break;
                default:
                    cout<<"Please enter valid option."<<endl;
            }
        }
    }
    
    
    bool displayOptions(){
        int choice = 0;
        bool exit = false;
        
        while (!exit){
            cout<< "What would you like to do today?\n1: Make a deposit\n2: Make a withdrawal\n3: Transfer money\n4: Get Balance\n5: Change PIN \n6: EXIT\n7: SIGN OUT\n\n" ;
            cin>>choice;
            double transfer=0;
            long inputCard=0;
            bool found = false;
            switch(choice){
                    
                    
                    //deposit
                case 1:
                    double deposit;
                    cout<<"Deposit amount: \n$";
                    cin>>deposit;
                    printf("\n");
                    allCustomers[currentCustomer].makeDeposit(deposit);
                    break;
                    
                    //withdrawal
                case 2:
                    double withdrawal;
                    cout<<"Withdrawal amount: \n$";
                    cin>>withdrawal;
                    printf("\n");
                    allCustomers[currentCustomer].makeWithdrawal(withdrawal);
                    break;
                    
                    //transfer
                case 3:
                    cout<<"Transfer amount: \n$";
                        //gets number from user input
                        double hold;
                        
                        //accepts input
                        std::cin >> hold;
                        
                        //erases any string
                        std::cin.clear();
                        std::cin.ignore(1000,'\n');
                        
                    transfer = hold;
                    printf("\n");
                    allCustomers[currentCustomer].makeTransfer(transfer);
                    
                    cout<<"Verify card number: \n";
                    cin >> inputCard;
                    for (int i = inputCard % 10; i < allCustomers.size(); i += 10){
                        if (allCustomers[i].getCardNumber() == inputCard){
                            this->transfer(inputCard,transfer);
                            found = true;
                            break;
                        }
                    }
                    if (!found){
                        cout<<"Invalid card number." << endl;
                    }
                    
                    break;
                    
                    //get balance
                case 4:
                    allCustomers[currentCustomer].getBalance();
                    break;
                    
                    //change PIN
                case 5:
                    allCustomers[currentCustomer].changePIN();
                    break;
                    
                    //exit
                case 6:
                    exit = true;
                    break;
                    
                    //sign out
                case 7:
                    exit = false;
                    displayMenu();
                    
                    break;
                    
            }
        }
        cout<<"\n";
        return exit;
        
    }
    
    
    
    long generateCardNumber(){
        long cardNumber = 0;
        for (int i = 0; i < 11; ++i)
        {
            cardNumber += rand() % 10;
            cardNumber *= 10;
        }
        
        cardNumber += cardLastDigit % 10;
        cardLastDigit++;
        
        return  cardNumber;
    }
    
    bool addNewCustomer(){
        string name;
        string address;
        long cardNumber;
        int PIN;
        int startingBalance;
        
        
        cout<<"Enter your name (First Last): ";
        getline(cin, name);
        
        
        cout<<"Enter your address: ";
        getline(cin, address);
        //cout << address << "\n";
        
        
        cardNumber = generateCardNumber();
        cout<<"Your new card number is : "<< cardNumber <<endl;
        
        cout<<"Enter a new PIN (Remember this PIN!): ";
        PIN = userInputNumber();
        //cout << PIN << "\n";
        
        cout << "Please enter your initial deposit (NUMBER ONLY): $";
        //accepts input
        std::cin >> startingBalance;
        
        //erases any string
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        
        allCustomers.push_back(Customer(name, address, cardNumber, startingBalance, PIN));
        
        setCurrentCustomer(cardNumber, true);
        
        
        return true;
    }
    
    //finish method below
    bool setCurrentCustomer(long cardNumber, bool madeAccount){
        //makes sure cardNumber is that of valid Customer
        currentCustomer = findCustomer(cardNumber);
        if (currentCustomer < 0) {
            return false;
        }
        
        Customer possibleCustomer = allCustomers[currentCustomer];
        int PIN;
        if (!madeAccount){
            //Gaurd for entering a PIN
            for (int i = 0; i < 3; i++){
                cout << "Please enter your PIN: ";
            
                // checks that user input is an integer
                PIN = userInputNumber();
            
                // Checks for correct PIN number
                if(possibleCustomer.comparePIN(PIN)){
                return true;
                }
                cout << "Incorret input. You have " << 2 - i << " attempts remaining." << endl;
            }
        }
        else {
            return true;
        }
        
        cout << "You have ran out of tries, please login again." << endl;
        currentCustomer = -1;
        return false;
    }
    
    Customer getCustomer(long cardNumber){
        int x = findCustomer(cardNumber);
        
        //if x is within the size of allCustomers returns the customer at that location
        if (x > -1) {
            return allCustomers[x];
        }
        
        //otherwise returns nullptr reference (NULL)
        return Customer("","",0,0,0);
    }
    
    
    
};



#endif /* main_h */
