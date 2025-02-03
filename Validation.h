#pragma once
#include <cctype>
#include <iostream>
using namespace std;
class Validation
{
	public:
    static bool validateName(string name)
    {
        if (name.length() < 5 || name.length() > 20)
            return false;
        for (char c : name)
        {
            if (!isalpha(c))
                return false;
        }
        return true;
    }

    static bool validatePassword(string password)
    {
        return (password.length() >= 8 && password.length() <= 20);
    }

    static bool validateBalance(double balance)
    {
        return (balance >= 1500);
    }

    static bool validateSalary(double salary)
    {
        return (salary >= 5000);
    }
};

