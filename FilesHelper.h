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
using namespace std;
//#include"Parser.h"
class FilesHelper
{
public:
    // ???? ???? ??? ID ?? ?????
    static void saveLast(const string& fileName, int id) {
        fstream file(fileName, ios::out);
        if (file.is_open()) {
            file << id;
            file.close();
        }
        else {
            throw runtime_error("Could not open " + fileName + " for writing.");
        }
    }

    // ???? ???????? ??? ID ?? ?????
    static int getLast(const string& fileName) {
        fstream file(fileName, ios::in);
        int lastId = 0;
        if (file.is_open()) {
            file >> lastId;
            file.close();
        }
        else {
            throw runtime_error("Could not open " + fileName + " for reading.");
        }
        return lastId;
    }
    static void saveClient(Client& c) {
        fstream file("client.txt", ios::app);
        if (file.is_open()) {
            file
                << c.getId() << ","
                << c.getName() << ","
                << c.getPassword() << ","
                << c.getBalanceEGP() << ","
                << c.getBalanceUSD() << endl;
            file.close();
        }
        else {
            throw runtime_error("Could not open client.txt for writing.");
        }
    }
    static void saveEmployee(Employee& e) {
        fstream file("Employees.txt", ios::app);
        if (file.is_open()) {
            file
                << e.getId() << ","
                << e.getName() << ","
                << e.getPassword() << ","
                << e.getSalary() << endl;
            file.close();
        }
        else {
            throw runtime_error("Could not open client.txt for writing.");
        }
    }
    static void saveAdmin(Admin& a) {
        fstream file("Admins.txt", ios::app);
        if (file.is_open()) {
            file
                << a.getId() << ","
                << a.getName() << ","
                << a.getPassword() << ","
                << a.getSalary() << endl;
            file.close();
        }
        else {
            throw runtime_error("Could not open client.txt for writing.");
        }
    }

    static vector<Client> getClients() {
        vector<Client>clients;
        ifstream File1;
        File1.open("Client.txt");
        if (File1.is_open())
        {
            string line;
            while (getline(File1, line))
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
            }File1.close();
        }
        else throw runtime_error("Could not open file client.txt for reading. ");
        return clients;
    }
    static vector<Employee>getEmployee() {
        vector<Employee>employees;
        ifstream File2;
        File2.open("Employees.txt");
        if (File2.is_open())
        {
            string line;
            while (getline(File2, line))
            {
                try
                {
                    Employee employee = Parser::parseToEmployee(line);
                    employees.push_back(employee);
                }
                catch (const exception& e)
                {
                    cout << "Error parsing client: " << e.what() << endl;
                }
            }File2.close();
        }
        else throw runtime_error("Could not open file client.txt for reading. ");
        return employees;
    }
    static void getAdmin() {
        vector<Admin>admins;
        ifstream File3;
        File3.open("Admins.txt");
        if (File3.is_open())
        {
            string line;
            while (getline(File3, line))
            {
                try
                {
                    Admin admin = Parser::parseToAdmin(line);
                    admins.push_back(admin);
                }
                catch (const exception& e)
                {
                    cout << "Error parsing client: " << e.what() << endl;
                }
            }File3.close();
        }
        else throw runtime_error("Could not open file client.txt for reading. ");
    }



    static void clearFile(const string& fileName, const string& lastIdFile) {
        fstream File;
        File.open(fileName, ios::out | ios::trunc);
        if (File.is_open())
        {
            File.close();
            saveLast(lastIdFile, 0);
        }
        else throw runtime_error("could not open " + fileName + " to clear.");
    }
};

