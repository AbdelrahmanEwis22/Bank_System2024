#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Validation {
public:
    static bool validateName(string name) {
        if (name.length() < 5 || name.length() > 20) return false;
        for (char c : name) {
            if (!isalpha(c)) return false;
        }
        return true;
    }

    static bool validatePassword(string password) {
        return (password.length() >= 8 && password.length() <= 20);
    }

    static bool validateBalance(double balance) {
        return (balance >= 1500);
    }

    static bool validateSalary(double salary) {
        return (salary >= 5000);
    }
};

class Person {
protected:
    int id;
    string name;
    string password;

public:
    // Constructor
    Person() {
        this->id = 0;
    }
    Person(int id, string name, string password) {
        this->id = id;
        this->name = name;
        this->password = password;
    }

    // Setters
    void setId(int id) {
        this->id = id;
    }
    void setName(string name) {
        if (!Validation::validateName(name))
            throw invalid_argument("Invalid name");
        this->name = name;
    }
    void setPassword(string password) {
        if (!Validation::validatePassword(password))
            throw invalid_argument("Weak password");
        this->password = password;
    }

    // Getters
    int getId() {
        return this->id;
    }
    string getName() {
        return this->name;
    }
    string getPassword() {
        return this->password;

    }
};

class Client : public Person {
private:
    double balance;

public:
    // Constructor
    Client() {
        this->balance = 0.0;
    }
    Client(int id, string name, string password, double balance)
        : Person(id, name, password) {
        this->balance = balance;
    }

    // Setters
    void setBalance(double balance) {
        if (!Validation::validateBalance(balance))
            throw invalid_argument("Minimum balance is 1500");
        this->balance = balance;
    }

    // Getters
    double getBalance() {
        return this->balance;
    }

    // Methods
    void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Invalid amount");
        balance += amount;
    }

    void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Invalid amount");
        if (balance - amount < 1500)
            throw invalid_argument("Cannot withdraw below 1500");
        balance -= amount;
    }

    void transferTo(Client& recipient, double amount) {
        withdraw(amount);
        recipient.deposit(amount);
    }

    void checkBalance() {
        cout << "Current balance: " << balance << endl;
    }

    void display() {
        cout << "ID: " << id << "\nName: " << name
            << "\nBalance: " << balance << endl;
    }
};

class Employee : public Person {
protected:
    double salary;

public:
    // Constructor
    Employee(int id, string name, string password, double salary)
        : Person(id, name, password) {
        this->salary = salary;
    }

    // Setters
    void setSalary(double salary) {
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
    void display() {
        cout << "ID: " << id << "\nName: " << name
            << "\nSalary: " << salary << endl;
    }
};

class Admin : public Employee {
private:
    double salary;
public:
    //cons
    Admin(int id, string name, string password, double salary)
        :Employee(id, name, password, salary) {
        this->salary = salary;
    }
    // using Employee::Employee; 
    //setter
    void setSalary(double salary) {
        if (!Validation::validateSalary(salary))
            throw invalid_argument("Minimum salary is 5000");
        this->salary = salary;
    }
    double getSalary()
    {
        return this->salary;
    }
    // Methods
    void display() {
        cout << "ID: " << id << "\nName: " << name
            << "\nSalary: " << salary << endl;
    }

};

int main() {
    Client client1(1, "Ahmed", "Ahmed12345", 2000);
    Client c2(2, "omar", "omar12345678", 2500);
    try {
        //Client client1(1, "Ahmed", "Ahmed12345", 2000);
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
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}



//كود  الاول

//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <map>
//#include <string>
//#include <algorithm>
//#include <limits>
//#include <sstream> 
//using namespace std;
//
//class Validation {
//public:
//    static bool validateName(string name) {
//        if (name.length() < 5 || name.length() > 20) return false;
//        for (char c : name) {
//            if (!isalpha(c)) return false;
//        }
//        return true;
//    }
//
//    static bool validatePassword(string password) {
//        return (password.length() >= 8 && password.length() <= 20);
//    }
//};
//
//// ========== الفئة الأساسية: Person ==========
//class Person {
//protected:
//    int id;
//    string name;
//    string password;
//    int loginAttempts = 0;
//
//public:
//    void setId(int id) { this->id = id; }
//    int getId() const { return id; } // const للأمان
//
//    void setName(string name) {
//        if (Validation::validateName(name)) this->name = name;
//        else cerr << "!Invalid name\n";
//    }
//
//    string getName() const { return name; } // إضافة دالة getName
//
//    void setPassword(string password) {
//        if (Validation::validatePassword(password)) this->password = password;
//        else cerr << "!Weak password\n";
//    }
//
//    bool verifyLogin(string inputPassword) {
//        if (loginAttempts >= 3) {
//            cerr << "!Too many attempts\n";
//            return false;
//        }
//        if (inputPassword == password) {
//            loginAttempts = 0;
//            return true;
//        }
//        else {
//            loginAttempts++;
//            cerr << "Remaining attempts: " << 3 - loginAttempts << endl;
//            return false;
//        }
//    }
//
//    void resetLoginAttempts() { loginAttempts = 0; }
//};
//
//// ========== فئة العميل ==========
//class Client : public Person {
//private:
//    double balance = 0;
//    double dailyWithdrawLimit = 5000;
//    double dailyWithdrawn = 0;
//    vector<string> transactionHistory;
//
//public:
//    void deposit(double amount) {
//        if (amount <= 0) {
//            cerr << "!Invalid amount\n";
//            return;
//        }
//        balance += amount;
//        transactionHistory.push_back(getCurrentTime() + " Deposit: +" + to_string(amount));
//        cout << "!Deposit successful\n";
//    }
//
//    void withdraw(double amount) {
//        if (amount <= 0) {
//            cerr << "!Invalid amount\n";
//            return;
//        }
//        if (amount > balance) {
//            cerr << "!Insufficient balance\n";
//        }
//        else if (dailyWithdrawn + amount > dailyWithdrawLimit) {
//            cerr << "!Daily withdrawal limit exceeded\n";
//        }
//        else {
//            balance -= amount;
//            dailyWithdrawn += amount;
//            transactionHistory.push_back(getCurrentTime() + " Withdrawal: -" + to_string(amount));
//            cout << "!Withdrawal successful\n";
//        }
//    }
//
//    void displayTransactions() const {
//        cout << "\nTransaction History:\n";
//        for (const string& t : transactionHistory) cout << t << endl;
//    }
//
//    string getCurrentTime() {
//        time_t now = time(0);
//        char buffer[80]; // مساحة كافية لتخزين الوقت
//        ctime_s(buffer, sizeof(buffer), &now); // استخدام ctime_s بشكل آمن
//        return string(buffer);
//    }
//};
//
//// ========== فئة الموظف ==========
//class Employee : public Person {
//private:
//    vector<Client> clients;
//
//public:
//    void addClient(Client& client) {
//        clients.push_back(client);
//        cout << "!Client added successfully\n";
//    }
//
//    void listClients() const {
//        cout << "\nClient List:\n";
//        for (const Client& c : clients) {
//            cout << "ID: " << c.getId() << " | Name: " << c.getName() << endl;
//        }
//    }
//};
//
//// ========== فئة الأدمن ==========
//class Admin : public Employee {
//public:
//    void deleteClient(vector<Client>& clients, int id) {
//        auto it = remove_if(clients.begin(), clients.end(), [id](const Client& c) {
//            return c.getId() == id;
//            });
//        if (it != clients.end()) {
//            clients.erase(it, clients.end());
//            cout << "!Client deleted\n";
//        }
//        else {
//            cout << "!Client not found\n";
//        }
//    }
//
//    void deleteEmployee(vector<Employee>& employees, int id) {
//        auto it = remove_if(employees.begin(), employees.end(), [id](const Employee& e) {
//            return e.getId() == id;
//            });
//        if (it != employees.end()) {
//            employees.erase(it, employees.end());
//            cout << "!Employee deleted\n";
//        }
//        else {
//            cout << "!Employee not found\n";
//        }
//    }
//};
//
//// ========== واجهات المستخدم ==========
//void clientMenu(Client& client) {
//    int choice;
//    do {
//        cout << "\n===== Client Menu =====" << endl;
//        cout << "1. Deposit\n2. Withdraw\n3. View Transactions\n4. Exit\nChoice: ";
//        string input;
//        cin >> input;
//        stringstream ss(input);
//        if (!(ss >> choice)) {
//            cerr << "!Invalid input\n";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            continue;
//        }
//
//        double amount;
//        switch (choice) {
//        case 1:
//            cout << "Amount: ";
//            cin >> amount;
//            client.deposit(amount);
//            break;
//        case 2:
//            cout << "Amount: ";
//            cin >> amount;
//            client.withdraw(amount);
//            break;
//        case 3:
//            client.displayTransactions();
//            break;
//        case 4:
//            cout << "Exiting...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (choice != 4);
//}
//
//void adminMenu(Admin& admin, vector<Client>& clients, vector<Employee>& employees) {
//    int choice, id;
//    do {
//        cout << "\n===== Admin Menu =====" << endl;
//        cout << "1. Delete Client\n2. Delete Employee\n3. Exit\nChoice: ";
//        string input;
//        cin >> input;
//        stringstream ss(input);
//        if (!(ss >> choice)) {
//            cerr << "!Invalid input\n";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            continue;
//        }
//
//        switch (choice) {
//        case 1:
//            cout << "Enter Client ID: ";
//            cin >> id;
//            admin.deleteClient(clients, id);
//            break;
//        case 2:
//            cout << "Enter Employee ID: ";
//            cin >> id;
//            admin.deleteEmployee(employees, id);
//            break;
//        case 3:
//            cout << "Exiting...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (choice != 3);
//}
//
//// ========== الدالة الرئيسية ==========
//int main() {
//    vector<Client> clients;
//    vector<Employee> employees;
//    Admin admin;
//    int mainChoice;
//
//    // بيانات تجريبية
//    Client c1;
//    c1.setId(1);
//    c1.setName("Ahmed");
//    c1.setPassword("12345678");
//    clients.push_back(c1);
//
//    do {
//        cout << "\n===== Banking System =====" << endl;
//        cout << "1. Client\n2. Employee\n3. Admin\n4. Exit\nChoice: ";
//        string input;
//        cin >> input;
//        stringstream ss(input);
//        if (!(ss >> mainChoice)) {
//            cerr << "!Invalid input\n";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            continue;
//        }
//
//        switch (mainChoice) {
//        case 1: {
//            int id;
//            string password;
//            cout << "Enter ID: ";
//            cin >> id;
//            cout << "Enter Password: ";
//            cin >> password;
//
//            auto it = find_if(clients.begin(), clients.end(), [id, password](Client& c) {
//                return (c.getId() == id) && (c.verifyLogin(password));
//                });
//
//            if (it != clients.end()) {
//                clientMenu(*it);
//            }
//            else {
//                cerr << "!Invalid login details\n";
//            }
//            break;
//        }
//        case 3: {
//            adminMenu(admin, clients, employees);
//            break;
//        }
//        case 4:
//            cout << "!Exiting program\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (mainChoice != 4);
//
//    return 0;
//}

//++++++++++++++++++++++++++++++++++++++++++
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <map>
//#include<string>
//#include <algorithm>
//#include <limits> // For handling user input
//using namespace std;
//
//// ========== Basic Validation Class ==========
//class Validation {
//public:
//    static bool validateName(string name) {
//        if (name.length() < 5 || name.length() > 20) return false;
//        for (char c : name) {
//            if (!isalpha(c)) return false;
//        }
//        return true;
//    }
//
//    static bool validatePassword(string password) {
//        return (password.length() >= 8 && password.length() <= 20);
//    }
//};
//
//// ========== Base Class: Person ==========
//class Person {
//protected:
//    int id;
//    string name;
//    string password;
//    string securityQuestion;
//    string securityAnswer;
//    int loginAttempts = 0;
//
//public:
//    void setId(int id) { this->id = id; }
//    int getId() { return id; }
//
//    void setName(string name) {
//        if (Validation::validateName(name)) this->name = name;
//        else cout << "!Invalid name\n";
//    }
//
//    void setPassword(string password) {
//        if (Validation::validatePassword(password)) this->password = password;
//        else cout << "!Weak password\n";
//    }
//
//    bool verifyLogin(string inputPassword) {
//        if (loginAttempts >= 3) {
//            cout << "!Too many attempts\n";
//            return false;
//        }
//        if (inputPassword == password) {
//            loginAttempts = 0;
//            return true;
//        }
//        else {
//            loginAttempts++;
//            cout << "Remaining attempts: " << 3 - loginAttempts << endl;
//            return false;
//        }
//    }
//
//    void resetLoginAttempts() { loginAttempts = 0; }
//};
//
//// ========== Client Class ==========
//class Client : public Person {
//private:
//    double balance = 0;
//    double dailyWithdrawLimit = 5000;
//    double dailyWithdrawn = 0;
//    vector<string> transactionHistory;
//
//public:
//    void deposit(double amount) {
//        balance += amount;
//        transactionHistory.push_back(getCurrentTime() + " Deposit: +" + to_string(amount));
//        cout << "!Deposit successful\n";
//    }
//
//    void withdraw(double amount) {
//        if (amount > balance) {
//            cout << "!Insufficient balance\n";
//        }
//        else if (dailyWithdrawn + amount > dailyWithdrawLimit) {
//            cout << "!Daily withdrawal limit exceeded\n";
//        }
//        else {
//            balance -= amount;
//            dailyWithdrawn += amount;
//            transactionHistory.push_back(getCurrentTime() + " Withdrawal: -" + to_string(amount));
//            cout << "!Withdrawal successful\n";
//        }
//    }
//
//    void displayTransactions() {
//        cout << "\nTransaction History:\n";
//        for (string t : transactionHistory) cout << t << endl;
//    }
//
//    string getCurrentTime() {
//        time_t now = time(0);
//        char buffer[26]; 
//        ctime_s(buffer, sizeof(buffer), &now); 
//        return string(buffer);
//    }
//
//};
//
//// ========== Employee Class ==========
//class Employee : public Person {
//private:
//    vector<Client> clients;
//
//public:
//    void addClient(Client& client) {
//        clients.push_back(client);
//        cout << "!Client added successfully\n";
//    }
//
//    /*void listClients() {
//        cout << "\nClient List:\n";
//        for (Client c : clients) {
//            cout << "ID: " << c.getId() << " | Name: " << c.getName() << endl;
//        }
//    }*/
//};
//
//// ========== Admin Class ==========
//class Admin : public Employee {
//public:
//    void deleteClient(vector<Client>& clients, int id) {
//        auto it = remove_if(clients.begin(), clients.end(), [id](Client c) {
//            return c.getId() == id;
//            });
//        if (it != clients.end()) {
//            clients.erase(it, clients.end());
//            cout << "!Client deleted\n";
//        }
//        else {
//            cout << "!Client not found\n";
//        }
//    }
//
//    void deleteEmployee(vector<Employee>& employees, int id) {
//        auto it = remove_if(employees.begin(), employees.end(), [id](Employee e) {
//            return e.getId() == id;
//            });
//        if (it != employees.end()) {
//            employees.erase(it, employees.end());
//            cout << "!Employee deleted\n";
//        }
//        else {
//            cout << "!Employee not found\n";
//        }
//    }
//};
//
//// ========== Currency Converter ==========
//class CurrencyConverter {
//private:
//    map<string, double> rates = { {"USD", 30.0}, {"EUR", 33.0} };
//
//public:
//    double convert(double amount, string from, string to) {
//        if (from == "EGP" && to == "USD") return amount / rates["USD"];
//        if (from == "USD" && to == "EGP") return amount * rates["USD"];
//        return amount; // More currencies can be added
//    }
//};
//
//// ========== User Interfaces ==========
//void clientMenu(Client& client) {
//    int choice;
//    do {
//        cout << "\n===== Client Menu =====" << endl;
//        cout << "1. Deposit\n2. Withdraw\n3. View Transactions\n4. Exit\nChoice: ";
//        cin >> choice;
//
//        double amount;
//        switch (choice) {
//        case 1:
//            cout << "Amount: ";
//            cin >> amount;
//            client.deposit(amount);
//            break;
//        case 2:
//            cout << "Amount: ";
//            cin >> amount;
//            client.withdraw(amount);
//            break;
//        case 3:
//            client.displayTransactions();
//            break;
//        case 4:
//            cout << "Exiting...\n";
//            break;
//        default:
//            cout << "!Invalid choice\n";
//        }
//    } while (choice != 4);
//}
//
//// ========== Main Function ==========
//int main() {
//    vector<Client> clients;
//    vector<Employee> employees;
//    Admin admin;
//    CurrencyConverter converter;
//    int mainChoice;
//
//    // Sample Data
//    Client c1;
//    c1.setId(1);
//    c1.setName("Ahmed");
//    c1.setPassword("12345678");
//    clients.push_back(c1);
//
//    do {
//        cout << "\n===== Banking System =====" << endl;
//        cout << "1. Client\n2. Employee\n3. Admin\n4. Exit\nChoice: ";
//        cin >> mainChoice;
//
//        switch (mainChoice) {
//        case 1: {
//            int id;
//            string password;
//            cout << "Enter ID: ";
//            cin >> id;
//            cout << "Enter Password: ";
//            cin >> password;
//
//            auto it = find_if(clients.begin(), clients.end(), [id, password](Client c) {
//                return (c.getId() == id) && (c.verifyLogin(password));
//                });
//
//            if (it != clients.end()) {
//                clientMenu(*it);
//            }
//            else {
//                cout << "!Invalid login details\n";
//            }
//            break;
//        }
//        case 4:
//            cout << "!Exiting program\n";
//            break;
//        default:
//            cout << "!Invalid choice\n";
//        }
//    } while (mainChoice != 4);
//
//    return 0;
//}

//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <map>
//#include <algorithm>
//#include <limits> // To handle user input
//using namespace std;
//
//// ========== Basic Classes ==========
//class Validation {
//public:
//    static bool validateName(string name) {
//        if (name.length() < 5 || name.length() > 20) return false;
//        for (char c : name) {
//            if (!isalpha(c)) return false;
//        }
//        return true;
//    }
//
//    static bool validatePassword(string password) {
//        return (password.length() >= 8 && password.length() <= 20);
//    }
//};
//
//// ========== Base Class: Person ==========
//class Person {
//protected:
//    int id;
//    string name;
//    string password;
//
//public:
//    void setId(int id) { this->id = id; }
//    int getId() { return id; }
//
//    void setName(string name) {
//        if (Validation::validateName(name)) this->name = name;
//        else cout << "!Invalid Name\n";
//    }
//
//    string getName() { return name; } // Added function to fix issue
//    void setPassword(string password) {
//        if (Validation::validatePassword(password)) this->password = password;
//        else cout << "!Weak Password\n";
//    }
//
//    string getPassword() { return password; }
//};
//
//// ========== Client Class ==========
//class Client : public Person {
//private:
//    double balance = 0;
//    double dailyWithdrawLimit = 5000;
//    double dailyWithdrawn = 0;
//    vector<string> transactionHistory;
//
//public:
//    void deposit(double amount) {
//        balance += amount;
//        transactionHistory.push_back(getCurrentTime() + " Deposit: +" + to_string(amount));
//        cout << "!Deposit Successful\n";
//    }
//
//    void withdraw(double amount) {
//        if (amount > balance) {
//            cout << "!Insufficient Balance\n";
//        }
//        else if (dailyWithdrawn + amount > dailyWithdrawLimit) {
//            cout << "!Daily Withdraw Limit Exceeded\n";
//        }
//        else {
//            balance -= amount;
//            dailyWithdrawn += amount;
//            transactionHistory.push_back(getCurrentTime() + " Withdraw: -" + to_string(amount));
//            cout << "!Withdrawal Successful\n";
//        }
//    }
//
//    void displayTransactions() {
//        cout << "\nTransaction History:\n";
//        for (string t : transactionHistory) cout << t << endl;
//    }
//
//    string getCurrentTime() {
//        time_t now = time(0);
//        return ctime(&now);
//    }
//};
//
//// ========== Employee Class ==========
//class Employee : public Person {
//protected:
//    vector<Client> clients;
//
//public:
//    void addClient(Client& client) {
//        clients.push_back(client);
//        cout << "!Client Added Successfully\n";
//    }
//
//    void listClients() {
//        cout << "\nClient List:\n";
//        for (Client& c : clients) {
//            cout << "ID: " << c.getId() << " | Name: " << c.getName() << endl;
//        }
//    }
//};
//
//// ========== Admin Class ==========
//class Admin : public Employee {
//public:
//    void deleteClient(int id) {
//        auto it = remove_if(clients.begin(), clients.end(), [id](Client& c) {
//            return c.getId() == id;
//            });
//
//        if (it != clients.end()) {
//            clients.erase(it, clients.end());
//            cout << "!Client Deleted\n";
//        }
//        else {
//            cout << "!Client Not Found\n";
//        }
//    }
//};
//
//// ========== Main Function ==========
//int main() {
//    vector<Client> clients;
//    vector<Employee> employees;
//    Admin admin;
//    int mainChoice;
//
//    // Sample Data
//    Client c1;
//    c1.setId(1);
//    c1.setName("Ahmed");
//    c1.setPassword("12345678");
//    clients.push_back(c1);
//
//    do {
//        cout << "\n===== Banking System =====" << endl;
//        cout << "1. Client\n2. Employee\n3. Admin\n4. Exit\nChoose: ";
//        cin >> mainChoice;
//
//        switch (mainChoice) {
//        case 1: {
//            int id;
//            string password;
//            cout << "Enter ID: ";
//            cin >> id;
//            cout << "Enter Password: ";
//            cin >> password;
//
//            auto it = find_if(clients.begin(), clients.end(), [id, password](Client& c) {
//                return (c.getId() == id) && (c.getPassword() == password);
//                });
//
//            if (it != clients.end()) {
//                cout << "!Login Successful\n";
//            }
//            else {
//                cout << "!Invalid Credentials\n";
//            }
//            break;
//        }
//        case 2: {
//            Employee employee;
//            employee.listClients();
//            break;
//        }
//        case 3: {
//            admin.listClients();
//            break;
//        }
//        case 4:
//            cout << "!Program Terminated\n";
//            break;
//        default:
//            cout << "!Invalid Choice\n";
//        }
//    } while (mainChoice != 4);
//
//    return 0;
//}

////كود بعد تعديلات تمام 
//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <string>
//#include <algorithm>
//#include <limits>
//#include <sstream>
//using namespace std;
//
//// ========== فئة التحقق من الصحة ==========
//class Validation {
//public:
//    static bool validateName(const string& name) {
//        if (name.length() < 5 || name.length() > 20) return false;
//        return all_of(name.begin(), name.end(), ::isalpha);
//    }
//
//    static bool validatePassword(const string& password) {
//        return (password.length() >= 8 && password.length() <= 20);
//    }
//};
//
//// ========== الفئة الأساسية: Person ==========
//class Person {
//protected:
//    int id;
//    string name;
//    string password;
//    int loginAttempts = 0;
//
//public:
//    void setId(int id) { this->id = id; }
//    int getId() const { return id; }
//
//    void setName(const string& name) {
//        if (Validation::validateName(name)) this->name = name;
//        else cerr << "!Invalid name\n";
//    }
//
//    string getName() const { return name; }
//
//    void setPassword(const string& password) {
//        if (Validation::validatePassword(password)) this->password = password;
//        else cerr << "!Weak password\n";
//    }
//
//    bool verifyLogin(const string& inputPassword) {
//        if (loginAttempts >= 3) {
//            cerr << "!Too many attempts\n";
//            return false;
//        }
//        if (inputPassword == password) {
//            loginAttempts = 0;
//            return true;
//        }
//        loginAttempts++;
//        cerr << "Remaining attempts: " << (3 - loginAttempts) << endl;
//        return false;
//    }
//
//    void resetPassword(const string& newPassword) {
//        if (Validation::validatePassword(newPassword)) {
//            password = newPassword;
//            cout << "!Password reset successful\n";
//        }
//        else {
//            cerr << "!Weak password\n";
//        }
//    }
//};
//
//// ========== فئة العميل ==========
//class Client : public Person {
//private:
//    double balance = 0;
//    double dailyWithdrawLimit = 5000;
//    double dailyWithdrawn = 0;
//    vector<string> transactionHistory;
//
//public:
//    void deposit(double amount) {
//        if (amount <= 0) {
//            cerr << "!Invalid amount\n";
//            return;
//        }
//        balance += amount;
//        transactionHistory.push_back(getCurrentTime() + " Deposit: +" + to_string(amount));
//        cout << "!Deposit successful. New balance: " << balance << endl;
//    }
//
//    void withdraw(double amount) {
//        if (amount <= 0) {
//            cerr << "!Invalid amount\n";
//            return;
//        }
//        if (amount > balance) {
//            cerr << "!Insufficient balance\n";
//            return;
//        }
//        if (dailyWithdrawn + amount > dailyWithdrawLimit) {
//            cerr << "!Daily withdrawal limit exceeded\n";
//            return;
//        }
//        balance -= amount;
//        dailyWithdrawn += amount;
//        transactionHistory.push_back(getCurrentTime() + " Withdrawal: -" + to_string(amount));
//        cout << "!Withdrawal successful. New balance: " << balance << endl;
//    }
//
//    void displayTransactions() const {
//        if (transactionHistory.empty()) {
//            cout << "!No transactions found\n";
//            return;
//        }
//        cout << "\nTransaction History:\n";
//        for (const string& t : transactionHistory) cout << t << endl;
//    }
//
//    double getBalance() const { return balance; }
//
//    string getCurrentTime() {
//        time_t now = time(0);
//        tm localTime;
//        localtime_r(&now, &localTime);
//
//        char buffer[80];
//        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &localTime);
//        return string(buffer);
//    }
//};
//
//// ========== فئة الموظف ==========
//class Employee : public Person {
//private:
//    vector<Client> clients;
//
//public:
//    void addClient(Client& client) {
//        clients.push_back(client);
//        cout << "!Client added successfully\n";
//    }
//
//    void listClients() const {
//        if (clients.empty()) {
//            cout << "!No clients found\n";
//            return;
//        }
//        cout << "\nClient List:\n";
//        for (const Client& c : clients) {
//            cout << "ID: " << c.getId() << " | Name: " << c.getName() << " | Balance: " << c.getBalance() << endl;
//        }
//    }
//};
//
//// ========== فئة الأدمن ==========
//class Admin : public Employee {
//public:
//    void deleteClient(vector<Client>& clients, int id) {
//        auto it = remove_if(clients.begin(), clients.end(), [id](const Client& c) {
//            return c.getId() == id;
//            });
//        if (it != clients.end()) {
//            clients.erase(it, clients.end());
//            cout << "!Client deleted\n";
//        }
//        else {
//            cout << "!Client not found\n";
//        }
//    }
//
//    void resetClientPassword(vector<Client>& clients, int id, const string& newPassword) {
//        auto it = find_if(clients.begin(), clients.end(), [id](const Client& c) {
//            return c.getId() == id;
//            });
//        if (it != clients.end()) {
//            it->resetPassword(newPassword);
//        }
//        else {
//            cout << "!Client not found\n";
//        }
//    }
//};
//
//// ========== واجهات المستخدم ==========
//void clientMenu(Client& client) {
//    int choice;
//    do {
//        cout << "\n===== Client Menu =====" << endl;
//        cout << "1. Deposit\n2. Withdraw\n3. View Transactions\n4. View Balance\n5. Exit\nChoice: ";
//        cin >> choice;
//
//        double amount;
//        switch (choice) {
//        case 1:
//            cout << "Amount: ";
//            cin >> amount;
//            client.deposit(amount);
//            break;
//        case 2:
//            cout << "Amount: ";
//            cin >> amount;
//            client.withdraw(amount);
//            break;
//        case 3:
//            client.displayTransactions();
//            break;
//        case 4:
//            cout << "Current Balance: " << client.getBalance() << endl;
//            break;
//        case 5:
//            cout << "!Exiting client menu...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (choice != 5);
//}
//
//void employeeMenu(Employee& employee) {
//    int choice;
//    do {
//        cout << "\n===== Employee Menu =====" << endl;
//        cout << "1. Add Client\n2. List Clients\n3. Exit\nChoice: ";
//        cin >> choice;
//
//        switch (choice) {
//        case 1: {
//            Client newClient;
//            int id;
//            string name, password;
//            cout << "Enter Client ID: ";
//            cin >> id;
//            cout << "Enter Client Name: ";
//            cin >> name;
//            cout << "Enter Client Password: ";
//            cin >> password;
//            newClient.setId(id);
//            newClient.setName(name);
//            newClient.setPassword(password);
//            employee.addClient(newClient);
//            break;
//        }
//        case 2:
//            employee.listClients();
//            break;
//        case 3:
//            cout << "!Exiting employee menu...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (choice != 3);
//}
//
//void adminMenu(Admin& admin, vector<Client>& clients) {
//    int choice;
//    do {
//        cout << "\n===== Admin Menu =====" << endl;
//        cout << "1. Delete Client\n2. Reset Client Password\n3. Exit\nChoice: ";
//        cin >> choice;
//
//        int id;
//        string newPassword;
//        switch (choice) {
//        case 1:
//            cout << "Enter Client ID: ";
//            cin >> id;
//            admin.deleteClient(clients, id);
//            break;
//        case 2:
//            cout << "Enter Client ID: ";
//            cin >> id;
//            cout << "Enter New Password: ";
//            cin >> newPassword;
//            admin.resetClientPassword(clients, id, newPassword);
//            break;
//        case 3:
//            cout << "!Exiting admin menu...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (choice != 3);
//}
//
//// ========== الدالة الرئيسية ==========
//int main() {
//    vector<Client> clients;
//    vector<Employee> employees;
//    Admin admin;
//    int mainChoice;
//
//    // بيانات تجريبية
//    Client c1;
//    c1.setId(1);
//    c1.setName("Ahmed");
//    c1.setPassword("12345678");
//    clients.push_back(c1);
//
//    do {
//        cout << "\n===== Banking System =====" << endl;
//        cout << "1. Client\n2. Employee\n3. Admin\n4. Exit\nChoice: ";
//        cin >> mainChoice;
//
//        int id;
//        string password;
//        switch (mainChoice) {
//        case 1: {
//            cout << "Enter ID: ";
//            cin >> id;
//            cout << "Enter Password: ";
//            cin >> password;
//
//            auto it = find_if(clients.begin(), clients.end(), [id, password](Client& c) {
//                return (c.getId() == id) && (c.verifyLogin(password));
//                });
//
//            if (it != clients.end()) {
//                cout << "\nWelcome, " << it->getName() << "!\n";
//                clientMenu(*it);
//            }
//            else {
//                cerr << "!Invalid login details\n";
//            }
//            break;
//        }
//        case 2: {
//            Employee emp;
//            employeeMenu(emp);
//            break;
//        }
//        case 3: {
//            adminMenu(admin, clients);
//            break;
//        }
//        case 4:
//            cout << "!Exiting program...\n";
//            break;
//        default:
//            cerr << "!Invalid choice\n";
//        }
//    } while (mainChoice != 4);
//
//    return 0;
//}