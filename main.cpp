#include <bits/stdc++.h>
#include "header.h"
using namespace std;

int main() {
    cout << "WELCOME TO THE PRODUCT RATING SYSTEM !!\n";
    cout << "Made by Joshua Erlangga\n\n";
    Products P; Customers C; Ratings R;
    initialize(P, C, R);
    int choice = -1;
    while (choice != 4) {
        anyKey(); mainMenu();
        cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "invalid choice\n\n";
            anyKey(); mainMenu();
            cin >> choice;
        }
        if (choice == 1) {
            adminMenu(P, C, R);
        } else if (choice == 2) {
            custMenu(P, C, R);
        } else if (choice == 3) {
            nonCustMenu(P, C, R);
        }
    }
    cout << "\nThank you for your visit!\nSee you next time.\n\n";
    anyKey();

    return 0;
}
