#include <cmath>

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
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
    void setName(string name)
    {
        if (!Validation::validateName(name))
            throw invalid_argument("Invalid name");
        this->name = name;
    }
    void setPassword(string password)
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

class Client : public Person
{
private:
    double balance;

public:
    // Constructor
    Client()
    {
        this->balance = 0.0;
    }
    Client(int id, string name, string password, double balance)
        : Person(id, name, password)
    {
        this->balance = balance;
    }

    // Setters
    void setBalance(double balance)
    {
        if (!Validation::validateBalance(balance))
            throw invalid_argument("Minimum balance is 1500");
        this->balance = balance;
    }

    // Getters
    double getBalance()
    {
        return this->balance;
    }

    // Methods
    void deposit(double amount)
    {
        if (amount <= 0)
            throw invalid_argument("Invalid amount");
        balance += amount;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
            throw invalid_argument("Invalid amount");
        if (balance - amount < 1500)
            throw invalid_argument("Cannot withdraw below 1500");
        balance -= amount;
    }

    void transferTo(Client &recipient, double amount)
    {
        withdraw(amount);
        recipient.deposit(amount);
    }

    void checkBalance()
    {
        cout << "Current balance: " << balance << endl;
    }

    void display()
    {
        cout << "ID: " << id << "\nName: " << name
             << "\nBalance: " << balance << endl;
    }
};

class Employee : public Person
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

class Admin : public Employee
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

int main()
{
    Client client1(1, "Ahmed", "Ahmed12345", 2000);
    Client c2(2, "omar", "omar12345678", 2500);
    try
    {
        // Client client1(1, "Ahmed", "Ahmed12345", 2000);
        /*client1.deposit(5000);
        client1.display();
        client1.withdraw(2000);
        client1.display();
        c2.display();*/
        client1.transferTo(c2, 500);
        client1.display();
        c2.display();
        c2.transferTo(client1, 1500);
        c2.checkBalance();
        client1.checkBalance();

        Employee emp1(101, "Mohamed", "MohamedPass", 6000);
        emp1.display();

        Admin admin(1001, "Admin", "AdminPass123", 10000);
        admin.display();
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
