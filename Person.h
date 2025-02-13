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
#include "Validation.h"
using namespace std;
class Person
{
	protected:
    int id;
    string name;
    string password;

public:
    // Constructor
    Person()
    {
        this->id = 0;
        this->name = " ";
        this->password = " ";
    }
    Person(int id, string name, string password)
    {
        setId(id);
        this->name = name;
        setPassword(password);
    }

    // Setters
    void setId(int id)
    {
        this->id = id;
    }
    void setName(std::string name)
    {
        if (!Validation::validateName(name))
            throw invalid_argument("Invalid name");
        this->name = name;
    }
    void setPassword(std::string password)
    {
        if (!Validation::validatePassword(password))
            throw invalid_argument("Weak password");
        this->password = password;
    }

    // Getters
    int getId()
    {
        return this->id;
    }
    string getName()
    {
        return this->name;
    }
    string getPassword()
    {
        return this->password;
    }
};

