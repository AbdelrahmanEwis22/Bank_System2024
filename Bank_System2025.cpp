#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
using namespace std;

void clientMenu(Client& client1, Client& client2) {
    try {
        int option;
        cout << "Select an operation:\n"
            << "1. Transfer within your own account (EGP to USD or USD to EGP)\n"
            << "2. Transfer to another client (EGP or USD)\n";
        cin >> option;
        client1.checkBalance();
        if (option == 1) {

            string fromCurrency, toCurrency;
            double amount;

            cout << "Enter the amount to transfer: ";
            cin >> amount;
            cout << "Enter the source currency (EGP/USD): ";
            cin >> fromCurrency;
            cout << "Enter the target currency (EGP/USD): ";
            cin >> toCurrency;
            cout << client1.getName() << ", the operation." << endl;
            client1.transferCurrency(client1, amount, fromCurrency, toCurrency);
            client1.checkBalance();
        }
        else if (option == 2) {
            int recipientId;
            string currency;
            double amount;

            cout << "Enter the recipient client ID (1 or 2): ";
            cin >> recipientId;

            cout << "Enter the amount to transfer: ";
            cin >> amount;
            cout << "Enter the currency (EGP/USD): ";
            cin >> currency;

            if (recipientId == client2.getId()) {
                client1.transferTo(client2, amount, currency);
            }
            else {
                throw invalid_argument("Invalid recipient ID.");
            }

            client1.checkBalance();
            client2.checkBalance();
        }
        else {
            cout << "Invalid option selected.\n";
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    Client client1(1, "Ahmed", "Ahmed12345",10000, 2000);
    Client client2(2, "omar", "omar12345678",20000, 2500);
    clientMenu(client1, client2);
    //try
    //{
    //    // Client client1(1, "Ahmed", "Ahmed12345", 2000);
    //    /*client1.deposit(5000);
    //    client1.display();
    //    client1.withdraw(2000);
    //    client1.display();
    //    c2.display();*/
    //    client1.transferTo(c2, 500);
    //    client1.display();
    //    c2.display();
    //    c2.transferTo(client1, 1500);
    //    c2.checkBalance();
    //    client1.checkBalance();

    //    Employee emp1(101, "Mohamed", "MohamedPass", 6000);
    //    emp1.display();

    //    Admin admin(1001, "Admin", "AdminPass123", 10000);
    //    admin.display();
    //}
    //catch (const exception &e)
    //{
    //    cerr << "Error: " << e.what() << endl;
    //}
    return 0;
}
