#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
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
    }
    Person(int id, string name, string password)
    {
        this->id = id;
        this->name = name;
        this->password = password;
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
    std::string getName()
    {
        return this->name;
    }
    std::string getPassword()
    {
        return this->password;
    }
};

