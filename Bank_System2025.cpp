#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
using namespace std;

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
