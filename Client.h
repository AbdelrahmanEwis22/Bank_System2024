#pragma once
#include <iostream>
#include "Person.h"
#include "Validation.h" 
using namespace std; 

class Client : public Person { 
private:
    double balanceEGP;
    double balanceUSD;

public:
    // Constructor
    Client() {
        this->balanceEGP = 0.0;
        this->balanceUSD = 0.0;
    }
    Client(int id, string name, string password, double balanceEGP, double balanceUSD)
        : Person(id, name, password) {
        this->balanceEGP = balanceEGP;
        this->balanceUSD = balanceUSD;
    }

    // Setters
    void setBalance(double balanceEGP) {
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
    double getBalance() {
        return this->balanceEGP;
    }
    double getBalanceUSD() {
        return this->balanceUSD;
    }

    // Methods
    void deposit(double amount, string currency) {
        if (amount <= 0) throw invalid_argument("Invalid amount");
        if (currency == "EGP")
            balanceEGP += amount;
        else if (currency == "USD")
            balanceUSD += amount;
        else throw invalid_argument("Invalid currency");
        cout << "Deposited " << amount << " " << currency << ".\n";
    }

    void withdraw(double amount, string currency) {
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
    }

    void transferTo(Client& recipient, double amount, string currency) {
        withdraw(amount, currency);
        recipient.deposit(amount, currency);
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
};

