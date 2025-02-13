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
class Parser
{
public:
    //static string trim(const string& str) {
    //    size_t first = str.find_first_not_of(" \t");
    //    if (first == string::npos) return ""; // ??? ???? ??????? ???? ??????
    //    size_t last = str.find_last_not_of(" \t");
    //    return str.substr(first, last - first + 1);
    //}
    static vector<string> split(string& line, char deli) {
        vector<string> tokens;
        stringstream ss(line);
        string token;
        while (getline(ss, token, deli)) {
            tokens.push_back(token);
        }
        return tokens;
    }

    static Client parseToClient(string& line) {
        vector<string> data = split(line, ',');
        if (data.size() != 5) {
            throw runtime_error("Invalid client data format.");
        }
        return Client(stoi(data[0]), data[1], data[2], stod(data[3]), stod(data[4]));
    }

    static Employee parseToEmployee(string& line) {
        vector<string> data = split(line, ',');
        if (data.size() != 4) {
            throw runtime_error("Invalid employee data format.");
        }
        return Employee(stoi(data[0]), data[1], data[2], stod(data[3]));
    }

    static Admin parseToAdmin(string& line) {
        vector<string> data = split(line, ',');
        if (data.size() != 4) {
            throw runtime_error("Invalid admin data format.");
        }
        return Admin(stoi(data[0]), data[1], data[2], stod(data[3]));
    }
};

