#include <iostream>
#include <string>
using namespace std;

// Base Class
class BankAccount {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;

public:
    BankAccount(string accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully!" << endl;
        } else {
            cout << "Invalid amount!" << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully!" << endl;
        } else {
            cout << "Insufficient balance or invalid amount!" << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    virtual void displayAccountDetails() {
        cout << "\n----- Account Details -----" << endl;
        cout << "Account Number : " << accountNumber << endl;
        cout << "Account Holder : " << accountHolderName << endl;
        cout << "Balance        : " << balance << endl;
    }

    // Virtual destructor
    virtual ~BankAccount() {}
};

// Savings Account
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    SavingsAccount(string accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() {
        double interest = balance * interestRate / 100;
        cout << "Interest Amount: " << interest << endl;
        balance += interest;
        cout << "Interest added to balance successfully!" << endl;
    }

    void displayAccountDetails() {
        BankAccount::displayAccountDetails();
        cout << "Account Type   : Savings Account" << endl;
        cout << "Interest Rate  : " << interestRate << "%" << endl;
    }
};

// Checking Account
class CheckingAccount : public BankAccount {
private:
    double overdraftLimit;

public:
    CheckingAccount(string accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            cout << "Amount withdrawn successfully!" << endl;
            if (balance < 0) {
                cout << "Warning: You are using overdraft facility." << endl;
            }
        } else {
            cout << "Transaction failed! Overdraft limit exceeded." << endl;
        }
    }

    void checkOverdraft() {
        if (balance < 0) {
            cout << "Account is in overdraft. Current balance: " << balance << endl;
        } else {
            cout << "No overdraft. Available balance: " << balance << endl;
        }
    }

    void displayAccountDetails() {
        BankAccount::displayAccountDetails();
        cout << "Account Type    : Checking Account" << endl;
        cout << "Overdraft Limit : " << overdraftLimit << endl;
    }
};

// Fixed Deposit Account
class FixedDepositAccount : public BankAccount {
private:
    int term; // in months

public:
    FixedDepositAccount(string accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal) {
        term = t;
    }

    void calculateInterest() {
        // Simple interest calculation (assuming 6% annual)
        double rate = 6.0;
        double interest = (balance * rate * term) / (100 * 12);
        cout << "Interest for " << term << " months: " << interest << endl;
        balance += interest;
        cout << "Interest added successfully!" << endl;
    }

    void displayAccountDetails() {
        BankAccount::displayAccountDetails();
        cout << "Account Type : Fixed Deposit Account" << endl;
        cout << "Term         : " << term << " months" << endl;
    }
};

int main() {
    BankAccount* accounts[3];

    // Creating different types of accounts
    accounts[0] = new SavingsAccount("SA001", "Rahul Sharma", 10000, 4.5);
    accounts[1] = new CheckingAccount("CA001", "Priya Patel", 5000, 2000);
    accounts[2] = new FixedDepositAccount("FD001", "Amit Kumar", 50000, 12);

    int choice;
    int accChoice;

    do {
        cout << "\n========= BANKING SYSTEM =========" << endl;
        cout << "1. Display Account Details" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Calculate Interest (Savings/FD)" << endl;
        cout << "5. Check Overdraft (Checking)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            cout << "\nSelect Account:" << endl;
            cout << "1. Savings Account (Rahul Sharma)" << endl;
            cout << "2. Checking Account (Priya Patel)" << endl;
            cout << "3. Fixed Deposit Account (Amit Kumar)" << endl;
            cout << "Enter choice: ";
            cin >> accChoice;

            if (accChoice < 1 || accChoice > 3) {
                cout << "Invalid account choice!" << endl;
                continue;
            }
        }

        switch (choice) {
            case 1:
                accounts[accChoice - 1]->displayAccountDetails();
                break;

            case 2: {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                accounts[accChoice - 1]->deposit(amount);
                break;
            }

            case 3: {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                accounts[accChoice - 1]->withdraw(amount);
                break;
            }

            case 4:
                if (accChoice == 1) {
                    ((SavingsAccount*)accounts[0])->calculateInterest();
                } else if (accChoice == 3) {
                    ((FixedDepositAccount*)accounts[2])->calculateInterest();
                } else {
                    cout << "Interest calculation not available for Checking Account." << endl;
                }
                break;

            case 5:
                if (accChoice == 2) {
                    ((CheckingAccount*)accounts[1])->checkOverdraft();
                } else {
                    cout << "Overdraft check only available for Checking Account." << endl;
                }
                break;

            case 6:
                cout << "Thank you for using Banking System!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 6);

    // Free memory
    for (int i = 0; i < 3; i++) {
        delete accounts[i];
    }

    return 0;
}