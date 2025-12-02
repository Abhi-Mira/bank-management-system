#include "BankAccount.h"

int main() {
    BankAccount acc;
    int choice;

    do {
        cout << "\n===== Secure Bank =====\n";
        cout << "1. Create Account\n2. Login\n3. Exit\nEnter choice: ";
        cin >> choice;

        switch(choice) {
            case 1: acc.createAccount(); break;
            case 2: acc.loginAccount(); break;
            case 3: cout << "\nThank you!\n"; break;
            default: cout << "\nInvalid Input!\n";
        }

    } while(choice != 3);

    return 0;
}

