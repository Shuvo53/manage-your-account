#include <iostream>
#include <vector>
#include <typeinfo>

using namespace std;

// Base class representing a generic bank account
class Account {
protected:
    int accountNumber;
    double balance;

public:
    Account(int accNum) : accountNumber(accNum), balance(0.0) {}

    void deposit(double amount) {
        balance += amount;
        cout << "Deposited: $" << amount << endl;
    }

    virtual void displayAccountInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
    }
};

// Derived class representing a savings account
class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(int accNum, double rate) : Account(accNum), interestRate(rate) {}

    void displayAccountInfo() override {
        cout << "-- Savings Account --" << endl;
        Account::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Derived class representing a checking account
class CheckingAccount : public Account {
private:
    int monthlyTransactionsLimit;

public:
    CheckingAccount(int accNum, int limit) : Account(accNum), monthlyTransactionsLimit(limit) {}

    void displayAccountInfo() override {
        cout << "-- Checking Account --" << endl;
        Account::displayAccountInfo();
        cout << "Monthly Transactions Limit: " << monthlyTransactionsLimit << endl;
    }
};

// Class representing a bank that manages a collection of accounts
class Bank {
public:
    vector<Account*> accounts;

public:
    void createAccount(int accNum, int accType) {
        Account* account = nullptr;
        if (accType == 1) {
            double interestRate;
            cout << "Enter interest rate: ";
            cin >> interestRate;
            account = new SavingsAccount(accNum, interestRate);
        } else if (accType == 2) {
            int monthlyTransactionsLimit;
            cout << "Enter monthly transactions limit: ";
            cin >> monthlyTransactionsLimit;
            account = new CheckingAccount(accNum, monthlyTransactionsLimit);
        }
        if (account != nullptr) {
            accounts.push_back(account);
            cout << "Account created successfully!" << endl;
        } else {
            cout << "Invalid account type!" << endl;
        }
    }

    void displayAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts found!" << endl;
            return;
        }

        for (Account* account : accounts) {
            account->displayAccountInfo();
            cout << endl;
        }
    }

    void searchAccountsByType(const string& accType) {
        vector<Account*> matchingAccounts;
        for (Account* account : accounts) {
            if (typeid(*account).name() == accType) {
                matchingAccounts.push_back(account);
            }
        }

        if (matchingAccounts.empty()) {
            cout << "No accounts of type " << accType << " found!" << endl;
            return;
        }

        cout << "Matching accounts of type " << accType << ":" << endl;
        for (Account* account : matchingAccounts) {
            account->displayAccountInfo();
            cout << endl;
        }
    }
};

int main() {
    Bank bank;

    while (true) {
        cout << "----- Banking System -----" << endl;
        cout << "1. Create Account" << endl;
        cout << "2. Display All Accounts" << endl;
        cout << "3. Search Accounts by Type" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int accountNumber, accountType;
            cout << "Enter account number: ";
            cin >> accountNumber;
            cout << "Enter account type (1: Savings, 2: Checking): ";
            cin >> accountType;
            bank.createAccount(accountNumber, accountType);
        } else if (choice == 2) {
            bank.displayAllAccounts();
        } else if (choice == 3) {
            string accountType;
            cout << "Enter account type: ";
            cin >> accountType;
            bank.searchAccountsByType(accountType);
        } else if (choice == 0) {
            break;
        } else {
            cout << "Invalid choice! Please try again." << endl;
        }

        cout << endl;
    }

    // Clean up allocated memory
    for (Account* account : bank.accounts) {
        delete account;
    }

    return 0;
}
