#pragma once
#include <iostream>
#include "Person.h"
#include "Validation.h" 
using namespace std; 

class Client : public Person { 
private:
    double balance;

public:
    // Constructor
    Client() {
        this->balance = 0.0;
    }
    Client(int id, string name, string password, double balance)
        : Person(id, name, password), balance(balance) {
        this->balance = balance;
    }

    // Setters
    void setBalance(double balance) {
        if (!Validation::validateBalance(balance))
            throw invalid_argument("Minimum balance is 1500");
        this->balance = balance;
    }

    // Getters
    double getBalance() {
        return this->balance;
    }

    // Methods
    void deposit(double amount) {
        if (amount <= 0)
            throw invalid_argument("Invalid amount");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0)
            throw invalid_argument("Invalid amount");
        if (balance - amount < 1500)
            throw invalid_argument("Cannot withdraw below 1500");
        balance -= amount;
    }

    void transferTo(Client& recipient, double amount) {
        withdraw(amount);
        recipient.deposit(amount);
    }

    void checkBalance() {
        cout << "Current balance: " << balance << endl;
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name
            << "\nBalance: " << balance << endl;
    }
};

