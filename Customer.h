//  ABSOLUTE FINAL VERSION AS OF NOW
//
//  Customer.h
//  ATM
//

#ifndef Header_h
#define Header_h


using namespace std;
int userInputNumber();

class Customer {
    friend class ATM;
    
private:
    string name;
    string address;
    string DOB;
    int cardNumber;
    int PIN;
    int balance;
    
public:
    Customer(string name, string address, string DOB, int cardNumber, double startingBalance, int PIN) {
        this->name = name;
        this->address = address;
        this->DOB = DOB;
        this->cardNumber = cardNumber;
        this->balance = (int)(startingBalance * 100);
        this->PIN = PIN;
    }
    
    bool changePIN() {
        int enteredPIN = -1;
        
        for (int i = 0; i < 3; i++) {
            cout << "Enter your current PIN (enter 0 to cancel): ";
            enteredPIN = userInputNumber();
            if (comparePIN(enteredPIN)) {
                
                for (int j = 0; j < 3; j++){
                    //accepts 2 user inputed PIN's to make sure new PIN is desired PIN
                    cout << "Please enter new PIN: ";
                    enteredPIN = userInputNumber();
                    if (enteredPIN == 0){
                        cout << "Process canceled";
                        return false;
                    }
                    int newPIN;
                    cout << "Please re-enter new PIN: ";
                    newPIN = userInputNumber();
                
                    //if 2 entered PIN's are same, set new PIN
                    if (newPIN == enteredPIN) {
                        this->PIN = newPIN;
                        cout << "Your PIN is now: " << newPIN << endl;
                        return true;
                    }
                
                    cout << "Entered PINS do not match. You have " << 2 - j << " attempts remaining." << endl;
                }
                
                cout << "Exiting current process." << endl;
                return false;
            }
            
            else {
                cout << "Incorrect PIN. You have " << 2 - i << " attempts remaining." << endl;
            }
            
        }
        
        cout << "Exiting current process." << endl;
        return false;
    }
    
    bool comparePIN(int PIN) {
        if (this->PIN == PIN) {
            return true;
        }
        return false;
    }
    
    bool compareCardNumber(int cardNumber) {
        if (this->cardNumber == cardNumber) {
            return true;
        }
        return false;
    }
    
    bool makeDeposit(double x) {
        this->balance += (int)(x * 100);
        return true;
    }
    
    bool makeWithdrawal(double x) {
        int withdrawalAmount = (int)(x * 100);
        //checks to make sure user has sufficient funds to make a withdrawal
        if (this->balance >= withdrawalAmount) {
            this->balance -= withdrawalAmount;
            return true;
        }
        
        cout << "Insufficient funds." << endl;
        return false;
    }
    
    double getBalance() {
        cout << "Your current balance is: " << ((double) this->balance) / 100 << endl;
        return this->balance;
    }
    
    bool compareTo(Customer x){
        if (name == x.name && DOB == x.DOB && address == x.address && balance == x.balance && PIN == x.PIN && cardNumber == x.cardNumber){
            return true;
        }
        return false;
    }
    
};

int userInputNumber() {
    //gets number from user input
    double hold;
    int size;
    
    //accepts input
    std::cin >> hold;
    
    //erases any string
    std::cin.clear();
    std::cin.ignore(1000,'\n');
    
    //checks if user entered a decimal
    if (hold != (int)hold){
        printf("You entered a decimal...\n");
        return -1;
    }
    
    size = (int) hold;
    return size;
}


#endif /* Header_h */
