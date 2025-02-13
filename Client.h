#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "Person.h"
#include "Validation.h" 
#include"FileManager.h"
using namespace std; 

class Client : public Person { 
private:
    double balanceEGP;
    double balanceUSD;
    vector<string> transactionHistory;

    static string getCurrentTime() {
        time_t now = time(0);
        struct tm tstruct;
        char buffer[80];
        localtime_s(&tstruct, &now);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tstruct);
        return string(buffer);
    }

public:
    // Constructor
    Client() {
        this->balanceEGP = 0.0;
        this->balanceUSD = 0.0;
    }
    Client(int id, string name, string password, double balanceEGP, double balanceUSD)
        : Person(id, name, password) {
        setBalanceEGP(balanceUSD); 
        setBalanceUSD(balanceUSD); 
    }

    // Setters
    void setBalanceEGP(double balanceEGP) {
        if (!Validation::validateBalance(balanceEGP))
            throw invalid_argument("Minimum balance is 1500");
        this->balanceEGP = balanceEGP;
    }
    void setBalanceUSD(double balanceUSD) {
        if (!Validation::validateBalance(balanceUSD))
            throw invalid_argument("Minimum balance is 1500");
        this->balanceUSD = balanceUSD;
    }

    // Getters
    double getBalanceEGP() {
        return this->balanceEGP;
    }
    double getBalanceUSD() {
        return this->balanceUSD;
    }

    // Methods
    void deposit(double amount, string currency, bool logTransaction = true) {
        if (amount <= 0) throw invalid_argument("Invalid amount");
        if (currency == "EGP")
            balanceEGP += amount;
        else if (currency == "USD")
            balanceUSD += amount;
        else throw invalid_argument("Invalid currency");
        cout << "Deposited " << amount << " " << currency << ".\n";
        ostringstream oss;
        oss << fixed << setprecision(2) << amount;
        transactionHistory.push_back(getCurrentTime() + " Deposit: +" + oss.str() + " " + currency);
    }

    void withdraw(double amount, string currency, bool logTransaction = true) {
        if (amount <= 0) throw invalid_argument("Invalid amount");
        if (currency == "EGP")
        {
            if (balanceEGP - amount < 1500)
                throw invalid_argument("Cannot withdraw below 1500");
            balanceEGP -= amount;
        }
        else if (currency == "USD")
        {
            if (balanceUSD - amount < 1500)
                throw invalid_argument("Cannot withdraw below 1500");
            balanceUSD -= amount;
        }
        else throw invalid_argument("Invalid currency");
        cout << "Withdrew  " << amount << " " << currency << ".\n";
        ostringstream oss;
        oss << fixed << setprecision(2) << amount;
        transactionHistory.push_back(getCurrentTime() + " Withdrawal: -" + oss.str() + " " + currency);
    }

    void transferTo(Client& recipient, double amount, string currency) {
        withdraw(amount, currency);
        recipient.deposit(amount, currency);
        ostringstream oss;
        oss << fixed << setprecision(2) << amount;
        transactionHistory.push_back(getCurrentTime() + " Transfer to " + recipient.getName() + ": -" + oss.str() + " " + currency);
        recipient.transactionHistory.push_back(getCurrentTime() + " Transfer from " + getName() + ": +" + oss.str() + " " + currency);
        cout << "Transferred " << amount << " " << currency << " to " << recipient.getName() << ".\n";
    }

    double convertCurrency(double amount, string from, string to) {
        if (from == "EGP" && to == "USD")
            return amount * 0.0199;
        else if (from == "USD" && to == "EGP")
            return amount * 50.28;
        else
            throw invalid_argument("Unsupported currency conversion.");
    }

    void transferCurrency(Client& recipient, double amount, string from, string to) {
        /* if (this == &recipient) {
             throw invalid_argument("Cannot transfer to the same client!");
         }*/
        double converted;
        if (from == "EGP" && to == "USD") {
            converted = convertCurrency(amount, from, to);
            withdraw(amount, "EGP");
            recipient.deposit(converted, "USD");
        }
        else if (from == "USD" && to == "EGP") {
            converted = convertCurrency(amount, from, to);
            withdraw(amount, "USD");
            recipient.deposit(converted, "EGP");
        }
        else {
            throw invalid_argument("Unsupported currency conversion.");
        }

        ostringstream oss;
        oss << fixed << setprecision(2) << amount;
        transactionHistory.push_back(getCurrentTime() + " Currency Transfer: " + oss.str() + " " + from + " to " + to);
        recipient.transactionHistory.push_back(getCurrentTime() + " Currency Received: " + oss.str() + " " + to + " from " + from);
        cout << "Transferred " << amount << " " << from << " to "
            << recipient.getName() << " in " << to << ".\n";
    }

    void checkBalance() {
        cout << "Current balance: " << balanceEGP << " EGP, "
            << balanceUSD << " USD.\n";
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name
            << "\nBalance: " << balanceEGP << " EGP, "
            << balanceUSD << " USD.\n";
    }
    void displayTransactions() {
        cout << "\nTransaction History for " << name << ":\n";
        for (const string& transaction : transactionHistory) {
            cout << transaction << endl;
        }
    }
    
};


