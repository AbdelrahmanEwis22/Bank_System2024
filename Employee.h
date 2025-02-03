#pragma once
#include <iostream>
#include <stdexcept>
#include "Person.h"
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
        this->salary = salary;
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
    void display()
    {
        cout << "ID: " << id << "\nName: " << name
             << "\nSalary: " << salary << endl;
    }
};

