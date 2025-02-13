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
using namespace std;
class Admin :public Employee
{
public:
    // cons
    Admin(int id, string name, string password, double salary)
        : Employee(id, name, password, salary)
    {
        setSalary(salary); 
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

   /* void addEmployee(Employee& employee) {
        FileManager().addEmployee(employee);
    }

    Employee* searchEmployee(int targetId) {
        vector<Employee> employees = FileManager().getAllEmployees();
        for (auto& emp : employees) {
            if (emp.getId() == targetId) {
                return new Employee(emp);
            }
        }
        return nullptr;
    }

    void editEmployee(int targetId, string newName, string newPassword, double newSalary) {
        vector<Employee> employees = FileManager().getAllEmployees();
        bool found = false;

        for (Employee& emp : employees) {
            if (emp.getId() == targetId) {
                emp = Employee(targetId, newName, newPassword, newSalary);
                found = true;
                break;
            }
        }

        if (found) {
            FileManager().removeAllEmployees();
            for (Employee& emp : employees) {
                FileManager().addEmployee(emp);
            }
        }
    }

    void listEmployees() {
        vector<Employee> employees = FileManager().getAllEmployees();
        cout << "===== All Employees =====" << endl;
        for ( Employee& e : employees) {
            cout << "ID: " << e.getId()
                << " | Name: " << e.getName()
                << " | Salary: " << e.getSalary() << endl;
        }
    }*/
};
    


