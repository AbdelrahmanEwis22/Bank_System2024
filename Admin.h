#pragma once
#include "Employee.h"
using namespace std;
class Admin :public Employee
{
	private:
    double salary;

public:
    // cons
    Admin(int id, string name, string password, double salary)
        : Employee(id, name, password, salary)
    {
        this->salary = salary;
    }
    // using Employee::Employee;
    // setter
    void setSalary(double salary)
    {
        if (!Validation::validateSalary(salary))
            throw invalid_argument("Minimum salary is 5000");
        this->salary = salary;
    }
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

