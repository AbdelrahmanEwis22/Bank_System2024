#pragma once
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>
#include<fstream>
#include "Person.h"
#include"Client.h"
#include"FileManager.h"
#include"Parser.h"
#include"Admin.h"
using namespace std;
class Employee :public Person
{
	protected:
    double salary;

public:
    // Constructor
    Employee(int id, string name, string password, double salary)
        : Person(id, name, password)
    {
        setSalary(salary); 
    }

    // Setters
    void setSalary(double salary)
    {
        if (!Validation::validateSalary(salary))
            throw invalid_argument("Minimum salary is 5000");
        this->salary = salary;
    }

    // Getters
    double getSalary()
    {
        return this->salary;
    }

    // Methods
    void addClient(Client& client) {
        FileManager().addClient(client); 
    }

    Client* searchClient(int targetId) {
        vector<Client> clients = FileManager().getAllClients();
        for (auto& client : clients) {
            if (client.getId() == targetId) {
                return new Client(client); // Return a copy
            }
        }
        return nullptr;
    }

    void listClients() {
        vector<Client> clients = FileManager().getAllClients(); 
        cout << "===== All Clients =====" << endl;
        for (Client& c : clients) {
            cout << "ID: " << c.getId()
                << " | Name: " << c.getName()
                << " | BalanceEGP: " << c.getBalanceEGP() 
                << " | BalanceUSD: " << c.getBalanceUSD() << endl;
        }
    }

    void editClient(int targetId, string newName, string newPassword, double newBalance) {
        vector<Client> clients = FileManager().getAllClients();
        bool found = false;

        // Update in memory
        for (Client& c : clients) {
            if (c.getId() == targetId) {
                c.setName(newName);
                c.setPassword(newPassword);
                c.setBalanceEGP(newBalance);
                c.setBalanceUSD(newBalance);
                found = true;
                break;
            }
        }

        // Rewrite entire file
        if (found) {
            FileManager().removeAllClients();
            for (Client& c : clients) {
                FileManager().addClient(c);
            }
        }
    }
    void display()
    {
        cout << "ID: " << id << "\nName: " << name
             << "\nSalary: " << salary << endl;
    }
};

