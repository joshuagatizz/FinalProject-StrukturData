#include <bits/stdc++.h>
#include "header.h"
using namespace std;

// MENU FUNCTIONS
void mainMenu() {
    cout << "~ Main Menu ~\n\n";
    cout << "1. Admin login\n2. Customer login\n3. Guest login\n4. Exit\nYour choice -> ";
}
void adminContext() {
    cout << "~ Admin Menu ~\n\n";
    cout << "1. Add new products\n2. View products\n3. Update products\n4. Delete products\n";
    cout << "5. View customers\n6. Delete customers\n7. Ratings by products\n8. Ratings by customers\n";
    cout << "9. Log out\nYour choice -> ";
}
void adminMenu(Products &P, Customers &C, Ratings &R) {
    int choice = -1;
    ptrcust data = NULL; logInAdm(C, data);
    if (data != NULL) {
        while (choice != 9) {
            anyKey();
            cout << "Hello admin " << info(data) << "!\n\n";
            adminContext();
            cin >> choice;
            while (choice < 1 || choice > 9) {
                cout << "Invalid choice\n\n";
                anyKey();
                cout << "Hello admin " << info(data) << "!\n\n";
                adminContext();
                cin >> choice;
            }
            if (choice == 1) {
                addProd(P);
            } else if (choice == 2) {
                viewProd(P);
            } else if (choice == 3) {
                updateProd(P);
            } else if (choice == 4) {
                deleteProd(P, R);
            } else if (choice == 5) {
                viewCust(C);
            } else if (choice == 6) {
                deleteCust(C, R);
            } else if (choice == 7) {
                viewRatByProd(R, P);
            } else if (choice == 8) {
                viewRatByCust(R, C);
            }
        }
    } else {
        int choice2;
        system("cls");
        cout << "Sorry, we couldn't log you in\nWhat do you want to do ?\n";
        cout << "1. Sign up / Log in as a guest\n2. Log in as a customer\n3. Back to main menu\nYour choice -> ";
        cin >> choice2;
        if (choice2 == 1) {
            nonCustMenu(P, C, R);
        } else if (choice2 == 2) {
            custMenu(P, C, R);
        }
    }
}
void custContext() {
    cout << "~ Customer Menu ~\n\n";
    cout << "1. Rate products\n2. Delete ratings\n3. View rated products\n";
    cout << "4. View unrated products\n5. Update profile\n6. Log out\nYour choice -> ";
}
void custMenu(Products &P, Customers &C, Ratings &R) {
    int choice = -1;
    ptrcust data = NULL; logInCust(C, data);
    if (data != NULL) {
        while (choice != 6) {
            anyKey();
            cout << "Hello " << info(data) << "!\n\n";
            custContext();
            cin >> choice;
            while (choice < 1 || choice > 6) {
                cout << "Invalid choice\n\n";
                anyKey();
                cout << "Hello " << info(data) << "!\n\n";
                custContext();
                cin >> choice;
            }
            if (choice == 1) {
                addRating(P, data, R);
            } else if (choice == 2) {
                deleteRev(P, R, data);
            } else if (choice == 3) {
                viewRatedProd(R, data);
            } else if (choice == 4) {
                viewUnratedProd(P, R, data);
            } else if (choice == 5) {
                updateProfile(C, data);
            }
        }
    } else {
        int choice2;
        system("cls");
        cout << "Sorry, we couldn't log you in\nWhat do you want to do ?\n";
        cout << "1. Sign up / Log in as a guest\n2. Back to main menu\nYour choice -> ";
        cin >> choice2;
        if (choice2 == 1) {
            nonCustMenu(P, C, R);
        }
    }
}
void nonCustContext() {
    cout << "~ Guest Menu ~\n\n";
    cout << "1. Sign up\n2. View all products and ratings\n3. Back to main menu\nYour choice -> ";
}
void nonCustMenu(Products &P, Customers &C, Ratings &R) {
    int choice = -1;
    while (choice != 3) {
        anyKey();
        cout << "Hello guest!\n\n";
        nonCustContext();
        cin >> choice;
        while (choice < 1 || choice > 3) {
            cout << "Invalid choice\n\n";
            choice = -1;
            anyKey();
            cout << "Hello guest!\n\n";
            nonCustContext();
            cin >> choice;
        }
        if (choice == 1) {
            signUp(C);
        } else if (choice == 2) {
            viewProductAndRating(P, R);
        }
    }
}
