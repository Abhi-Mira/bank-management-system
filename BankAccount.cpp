#include "BankAccount.h"

void BankAccount::createAccount() {
    cin.ignore();
    cout << "\nEnter Full Name: ";
    getline(cin, name);

    cout << "Enter Email: ";
    getline(cin, email);

    cout << "Enter Phone Number: ";
    getline(cin, phone);

    cout << "Enter Aadhar Number: ";
    getline(cin, aadhar);

    cout << "Create Password: ";
    getline(cin, password);

    cout << "Create Account Number: ";
    getline(cin, accountNumber);

    sqlite3* DB;
    sqlite3_open("bank.db", &DB);

    string sql = "INSERT INTO accounts VALUES('" + accountNumber + "','" + name + "','" +
        password + "','" + email + "','" + phone + "','" + aadhar + "',0);";

    char* errMsg;
    if (sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, &errMsg) == SQLITE_OK)
        cout << "\n✔ Account Created Successfully!\n";
    else
        cout << "\n❌ Error: Account Probably Already Exists!\n";

    sqlite3_close(DB);
}

void BankAccount::loginAccount() {
    cin.ignore();
    cout << "\nEnter Account Number: ";
    getline(cin, accountNumber);

    cout << "Enter Password: ";
    getline(cin, password);

    sqlite3* DB;
    sqlite3_open("bank.db", &DB);

    string sql = "SELECT name,password,balance FROM accounts WHERE accountNumber='" + accountNumber + "';";
    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, nullptr);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        string storedPass = (const char*)sqlite3_column_text(stmt, 1);
        balance = sqlite3_column_double(stmt, 2);

        if (password == storedPass) {
            cout << "\n✔ Login Success!\n";
            sqlite3_finalize(stmt);
            sqlite3_close(DB);
            mainMenu();
            return;
        }
    }

    cout << "\n❌ Invalid Account or Password!\n";
    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

void BankAccount::depositMoney() {
    double amount;
    cout << "\nEnter Deposit Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "❌ Invalid Amount\n";
        return;
    }

    sqlite3* DB;
    sqlite3_open("bank.db", &DB);

    balance += amount;

    string sql = "UPDATE accounts SET balance=" + to_string(balance) +
        " WHERE accountNumber='" + accountNumber + "';";

    sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, nullptr);

    cout << "✔ Money Deposited!\n";

    sqlite3_close(DB);
}

void BankAccount::withdrawMoney() {
    double amount;
    cout << "\nEnter Withdraw Amount: ";
    cin >> amount;

    if (amount > balance) {
        cout << "❌ Insufficient Balance\n";
        return;
    }

    sqlite3* DB;
    sqlite3_open("bank.db", &DB);

    balance -= amount;

    string sql = "UPDATE accounts SET balance=" + to_string(balance) +
        " WHERE accountNumber='" + accountNumber + "';";

    sqlite3_exec(DB, sql.c_str(), nullptr, nullptr, nullptr);

    cout << "✔ Money Withdrawn!\n";

    sqlite3_close(DB);
}

void BankAccount::checkBalance() {
    cout << "\n💰 Current Balance: " << balance << endl;
}

void BankAccount::accountDetails() {
    cout << "\n📌 Account Details:\n";
    cout << "Name: " << name << endl;
    cout << "Account Number: " << accountNumber << endl;
    cout << "Email: " << email << endl;
    cout << "Phone: " << phone << endl;
    cout << "Aadhar: " << aadhar << endl;
    cout << "Balance: " << balance << endl;
}

void BankAccount::mainMenu() {
    int option;
    
    do {
        cout << "\n----- MENU -----\n";
        cout << "1. Deposit\n2. Withdraw\n3. Check Balance\n4. Account Details\n5. Logout\nChoice: ";
        cin >> option;

        switch(option) {
            case 1: depositMoney(); break;
            case 2: withdrawMoney(); break;
            case 3: checkBalance(); break;
            case 4: accountDetails(); break;
            case 5: cout << "Logging out...\n"; break;
            default: cout << "Invalid Option!\n";
        }
    } while(option != 5);
}
