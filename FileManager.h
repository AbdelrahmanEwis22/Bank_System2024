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
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
#include"Parser.h"
using namespace std;
class FileManager 
{
protected:
    //files name
    string ClientFile = "client.txt";
    string EmployeesFile = "Employees.txt";
    string AdminsFile = "Admins.txt";
public:
    //AddFiles
    void addClient(Client& client) {
        ofstream MyFile1(ClientFile, ios::app);
        if (MyFile1.is_open())
        {
            MyFile1
                << client.getId() << ","
                << client.getName() << ","
                << client.getPassword() << ","
                << client.getBalanceEGP() << ","
                << client.getBalanceUSD() << endl;
            MyFile1.close();
        }
        else throw runtime_error("Could not open Clients.txt for writing.");
    }
    void addEmployee(Employee& employee) {
        fstream MyFile2(EmployeesFile, ios::app);
        if (MyFile2.is_open())
        {
            MyFile2
                << employee.getId() << ","
                << employee.getName() << ","
                << employee.getPassword() << ","
                << employee.getSalary() << endl;
            MyFile2.close();
        }
        else throw runtime_error("Could not open Employee.txt for writing.");
    }
    void addAdmin(Admin& admin) {
        fstream MyFile3(AdminsFile, ios::app);
        if (MyFile3.is_open())
        {
            MyFile3
                << admin.getId() << ","
                << admin.getName() << ","
                << admin.getPassword() << ","
                << admin.getSalary() << endl;
            MyFile3.close();
        }
        else throw runtime_error("Could not open Admin.txt for writing.");
    }
    //RemoveAllFiles
    void removeAllClients() {
        fstream MyFile1(ClientFile, ios::out | ios::trunc); // ???? ?? ??? ????? ???? ????
        if (MyFile1.is_open())
            MyFile1.close();
        else throw runtime_error("Could not open Clients.txt to remove.");
    }
    void removeAllEmployees() {
        fstream MyFile2(EmployeesFile, ios::trunc);
        if (MyFile2.is_open())
            MyFile2.close();
        else throw runtime_error("Could not open Employees.txt to remove.");
    } void removeAllAdmins() {
        fstream MyFile3(AdminsFile, ios::trunc);
        if (MyFile3.is_open())
            MyFile3.close();
        else throw runtime_error("Could not open Admins.txt to remove.");
    }
    //GetAllFiles
    vector<Client> getAllClients() {
        vector<Client>clients{};
        ifstream MyFile1;
        MyFile1.open(ClientFile);
        if (MyFile1.is_open())
        {
            string line;
            while (getline(MyFile1, line))
            {
                try
                {
                    Client client = Parser::parseToClient(line);
                    clients.push_back(client);
                }
                catch (const exception& e)
                {
                    cout << "Error parsing client: " << e.what() << endl;
                }
            }MyFile1.close();
        }
        else throw runtime_error("Could not open file: " + ClientFile);
        return clients;
    }
    vector<Employee> getAllEmployees() {
        vector<Employee>employees{};
        ifstream MyFile2;
        if (MyFile2.is_open())
        {
            string line;
            while (getline(MyFile2, line))
            {
                vector<string>data = Parser::split(line, ',');
                if (data.size() == 4)
                {
                    Employee employee = Parser::parseToEmployee(line);
                    employees.push_back(employee);
                }
            }MyFile2.close();
        }
        else throw runtime_error("Could not open file: " + EmployeesFile);
        return employees;
    }
    vector<Admin> getAllAdmins() {
        vector<Admin> admins;
        ifstream MyFile3;
        if (MyFile3.is_open())
        {
            string line;
            while (getline(MyFile3, line))
            {
                vector<string>data = Parser::split(line, ',');
                if (data.size() == 4)
                {
                    Admin admin = Parser::parseToAdmin(line);
                    admins.push_back(admin);
                }
            }MyFile3.close();
        }
        else throw runtime_error("Could not open file: " + AdminsFile);
        return admins;
    }
};

