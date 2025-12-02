#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <sqlite3.h>
using namespace std;

class BankAccount {
private:
    string accountNumber, name, password, email, phone, aadhar;
    double balance = 0;

public:
    void createAccount();
    void loginAccount();
    void mainMenu();
    void depositMoney();
    void withdrawMoney();
    void checkBalance();
    void accountDetails();
};

#endif
