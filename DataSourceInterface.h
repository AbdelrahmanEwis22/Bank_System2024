#pragma once
#include <vector>
#include <iostream>
#include "Client.h"
#include "Admin.h"
#include "Employee.h"
using namespace std;
class DataSourceInterface
{
public:
	virtual void addClient(Client) = 0;
	virtual	void addEmployee(Employee) = 0;
	virtual void addAdmin(Admin) = 0;
	virtual vector<Client> getAllClients() = 0;
	virtual vector<Employee>getAllEmployees() = 0;
	virtual vector<Employee>getAllAdmins() = 0;
	virtual void removeAllClients() = 0;
	virtual  void removeAllEmployees() = 0;
	virtual void removeAllAdmins() = 0;
};

