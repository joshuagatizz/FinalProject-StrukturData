#include <bits/stdc++.h>
#include "header.h"
using namespace std;

// SUPPORTING FUNCTIONS

void anyKey() {
    system("pause");
    system("cls");
}
void initialize(Products &P, Customers &C, Ratings &R) {
    first(P) = NULL;
    first(C) = NULL;
    first(R) = NULL;
}

void signUp(Customers &C) {
    string name, user, pass;
    cout << "Username : "; cin >> user;
    while (checkDuplicateNames(C, user)) {
        cout << "this username has already taken\n";
        cout << "Username : "; cin >> user;
    }
    cout << "Password : "; cin >> pass;
    cout << "Name : "; getline(cin >> ws, name);
    ptrcust p = createCust(name, user, pass);
    // insert by username
    if (first(C) == NULL) {
        first(C) = p;
    } else {
        ptrcust a = first(C), b;
        bool inserted = false;
        if (user < user(a)) {
            next(p) = first(C);
            first(C) = p;
            inserted = true;
        } else {
            while (next(a) != NULL && !inserted) {
                b = a;
                a = next(a);
                if (user < user(a)) {
                    next(p) = a;
                    next(b) = p;
                    inserted = true;
                }
            }
            if (!inserted) {
                next(a) = p;
            }
        }
    }
}
void logInAdm(Customers C, ptrcust &data) {
    string specialcode = "12345", user, pass, code, choice = "y";
    cout << "Please login with your account\n";
    cout << "Username : "; cin >> user;
    cout << "Password : "; cin >> pass;
    cout << "Admin code : "; cin >> code;
    while (searchCust(C, user, pass) == NULL || code != specialcode) {
        cout << "Your username or password or code is incorrect\nDo you want to try again?\n";
        cout << "type ""y"" for yes and ""n"" for no\nYour choice -> ";
        cin >> choice;
        if (choice == "n") {
            break;
        }
        cout << "Username : "; cin >> user;
        cout << "Password : "; cin >> pass;
        cout << "Admin code : "; cin >> code;
    }
    if (choice == "y") {
        data = searchCust(C, user, pass);
    }
}
void logInCust(Customers C, ptrcust &data) {
    string user, pass, choice = "y";
    cout << "Please login with your account\n";
    cout << "Username : "; cin >> user;
    cout << "Password : "; cin >> pass;
    while (searchCust(C, user, pass) == NULL) {
        cout << "Your username or password is incorrect\nDo you want to try again?\n";
        cout << "type ""y"" for yes and ""n"" for no\nYour choice -> ";
        cin >> choice;
        if (choice == "n") {
            break;
        }
        cout << "Username : "; cin >> user;
        cout << "Password : "; cin >> pass;
    }
    if (choice == "y") {
        data = searchCust(C, user, pass);
    }
}

void addProd(Products &P) {
    string prod;
    cout << "Please enter the product's name -> "; getline(cin >> ws, prod);
    if (!checkDuplicateProd(P, prod)) {
        //insert first
        ptrprod a = createProd(prod);
        next(a) =first(P);
        first(P) = a;
    } else {
        cout << "This product has already exist\n";
    }
}
void addRating(Products &P, ptrcust &c, Ratings &R) {
    ptrprod a = first(P);
    if (a == NULL) {
        cout << "There are currently no product to rate right now\n";
    } else {
        string choice;
        while (choice != "-1") {
            anyKey();
            viewProd(P);
            cout << "Which product do you want to rate?\nType -1 if you're done\nYour choice -> ";
            getline(cin >> ws, choice);
            while (searchProd(P, choice) == NULL && choice !=  "-1") {
                cout << "Product does not exist\nProduct's name -> ";
                getline(cin >> ws, choice);
            }
            if (searchProd(P, choice) != NULL && choice != "-1") {
                ptrprod a = searchProd(P, choice);
                ptrcust b = c; int rat;
                if (searchRev(R, user(c), info(a)) != NULL) {
                    cout << "You have rated this product before\n";
                    cout << "Would you like to update your rating? (y/n) \n";
                    string choice2; cin >> choice2;
                    if (choice2 == "y") {
                        cout << "Your new rating (1-10) -> "; cin >> rat;
                        while (rat < 0 || rat > 10) {
                            cout << "Please input a number between 1 and 10\n";
                            cout << "Your rating -> "; cin >> rat;
                        }
                        ptrrev x = searchRev(R, user(c), info(a));
                        info(x) = rat;
                        cout << "Your rating is in. Thank you!\n";
                    }
                } else {
                    cout << "What rating will you give to this product? (1-10)\n";
                    cout << "Your rating -> "; cin >> rat;
                    while (rat < 0 || rat > 10) {
                        cout << "Please input a number between 1 and 10\n";
                        cout << "Your rating -> "; cin >> rat;
                    }
                    ptrrev ins = createRev(R, rat, a, b);
                    // insert first
                    next(ins) = first(R);
                    first(R) = ins;
                    cout << "Your rating is in. Thank you!\n";
                }
            }
        }
    }
}

bool checkDuplicateNames(Customers C, string s) {
    ptrcust a = first(C);
    bool found = false;
    if (a != NULL) {
        if (user(a) == s) {
            found = true;
        }
        while (next(a) != NULL && !found) {
            a = next(a);
            if (user(a) == s) {
                found = true;
            }
        }
    }
    return found;
}
bool checkDuplicateProd(Products P, string s) {
    ptrprod a = first(P);
    bool found = false;
    if (a != NULL) {
        if (info(a) == s) {
            found = true;
        }
        while (next(a) != NULL && !found) {
            a = next(a);
            if (info(a) == s) {
                found = true;
            }
        }
    }
    return found;
}

ptrcust createCust(string name, string user, string pass) {
    ptrcust ret = new elmCust;
    info(ret) = name;
    user(ret) = user;
    pass(ret) = pass;
    next(ret) = NULL;
    return ret;
}
ptrprod createProd(string name) {
    ptrprod ret = new elmProd;
    next(ret) = NULL;
    info(ret) = name;
    return ret;
}
ptrrev createRev(Ratings &R, int rat, ptrprod a, ptrcust b) {
    ptrrev ret = new elmRev;
    next(ret) = NULL;
    rever(ret) = b;
    revee(ret) = a;
    info(ret) = rat;
    return ret;
}

void viewProd(Products P) {
    ptrprod a = first(P);
    if (a != NULL) {
        cout << "\n-Products List-\n";
        cout << "- " << info(a) << "\n";
        while (next(a) != NULL) {
            a = next(a);
            cout << "- " << info(a) << "\n";
        }
    } else {
        cout <<"\nThere are not any product to show\n";
    }
}
void viewCust(Customers C) {
    ptrcust a = first(C);
    if (a != NULL) {
        cout << "\n-Customers List-\n";
        cout << "- " << user(a) << "\n";
        while (next(a) != NULL) {
            a = next(a);
            cout << "- " << user(a) << "\n";
        }
    } else {
        cout <<"\nThere are not any customer to show\n";
    }
}
void viewRatedProd(Ratings R, ptrcust c) {
    bool have =  false;
    ptrrev a = first(R);
    cout << "\n-" << user(c) << "'s Rated Products-\n";
    if (a != NULL) {
        if (rever(a) == c) {
            cout << "- " <<info(revee(a)) << " : " << info(a) << " out of 10\n";
            have = true;
        }
        while (next(a) != NULL) {
            a =  next(a);
            if (rever(a) == c) {
                cout << "- " <<info(revee(a)) << " : " << info(a) << " out of 10\n";
                have = true;
            }
        }
    }
    if (!have) {
        cout << "\nThere is none\n";
    }
}
void viewUnratedProd(Products P, Ratings R, ptrcust c) {
    bool have = false;
    ptrprod b = first(P);
    ptrrev a = first(R);
    cout << "\n-" << user(c) << "'s Unrated Products-\n";
    if (a != NULL && b != NULL) {
        a = searchRev(R, user(c), info(b));
        if (a == NULL) {
            cout << "- " << info(b) << "\n";
            have = true;
        }
        while (next(b) != NULL) {
            b = next(b);
            a = searchRev(R, user(c), info(b));
            if (a == NULL) {
                cout << "- " << info(b) << "\n";
                have = true;
            }
        }
    }
    if (!have) {
        cout << "\nThere is none\n";
    }
}
void viewRatByProd(Ratings R, Products P) {
    ptrprod a = first(P);
    if (a != NULL) { //prod
        cout << "\nProduct : " << info(a) << "\n";
        ptrrev b = first(R);
        bool rated = false;
        if (b != NULL) { //rev
            if (revee(b) == a) {
                cout << "- " << user(rever(b)) << ", " << info(b) << " out of 10\n";
                rated = true;
            }
            while (next(b) != NULL) {
                b = next(b);
                if (revee(b) == a) {
                    cout << "- " << user(rever(b)) << ", " << info(b) << " out of 10\n";
                    rated = true;
                }
            }
        }
        if (!rated) {
            cout << "No rating\n";
        }
        while (next(a) != NULL) {
            a = next(a);
            cout << "Product : " << info(a) << "\n";
            ptrrev b = first(R);
            bool rated = false;
            if (b != NULL) { //rev
                if (revee(b) == a) {
                    cout << "- " << user(rever(b)) << ", " << info(b) << " out of 10\n";
                    rated = true;
                }
                while (next(b) != NULL) {
                    b = next(b);
                    if (revee(b) == a) {
                        cout << "- " << user(rever(b)) << ", " << info(b) << " out of 10\n";
                        rated = true;
                    }
                }

            }
            if (!rated) {
                cout << "No rating\n";
            }
        }
    } else {
        cout << "\nThere is no product to show\n";
    }
}
void viewRatByCust(Ratings R, Customers C) {
    ptrcust a = first(C);
    if (a != NULL) { //cust
        cout << "\nCustomer : " << user(a) << "\n";
        ptrrev b = first(R);
        bool rated = false;
        if (b != NULL) { //rev
            if (rever(b) == a) {
                cout << "- " << info(revee(b)) << ", " << info(b) << " out of 10\n";
                rated = true;
            }
            while (next(b) != NULL) {
                b = next(b);
                if (rever(b) == a) {
                    cout << "- " << info(revee(b)) << ", " << info(b) << " out of 10\n";
                    rated = true;
                }
            }
        }
        if (!rated) {
            cout << "No rating\n";
        }
        while (next(a) != NULL) {
            a = next(a);
            cout << "Customer : " << user(a) << "\n";
            ptrrev b = first(R);
            bool rated = false;
            if (b != NULL) { //rev
                if (rever(b) == a) {
                    cout << "- " << info(revee(b)) << ", " << info(b) << " out of 10\n";
                    rated = true;
                }
                while (next(b) != NULL) {
                    b = next(b);
                    if (rever(b) == a) {
                        cout << "- " << info(revee(b)) << ", " << info(b) << " out of 10\n";
                        rated = true;
                    }
                }
            }
            if (!rated) {
                cout << "No rating\n";
            }
        }
    } else {
        cout << "\nThere is no customer to show\n";
    }
}
void viewProductAndRating(Products P, Ratings R) {
    struct avgprod {
        ptrprod prodinfo;
        float prodrat;
        int countrat;
    };
    avgprod arr[100];
    int tail = 0;
    ptrprod a = first(P);
    if (a != NULL) {
        arr[tail].prodinfo = a;
        ptrrev b = first(R);
        int sum = 0, counter = 0;
        if (b != NULL) {
            if (revee(b) == a) {
                sum += info(b);
                counter++;
            }
            while (next(b) != NULL) {
                b = next(b);
                if (revee(b) == a) {
                    sum += info(b);
                    counter++;
                }
            }
        }
        if (sum == 0 && counter == 0) {
            arr[tail].prodrat = 0;
            arr[tail].countrat = 0;
        } else {
            arr[tail].prodrat = float(sum) / float(counter);
            arr[tail].countrat = counter;
        }
        tail++;
        while (next(a) != NULL) {
            a = next(a);
            arr[tail].prodinfo = a;
            ptrrev b = first(R);
            sum = 0; counter = 0;
            if (b != NULL) {
                if (revee(b) == a) {
                    sum += info(b);
                    counter++;
                }
                while (next(b) != NULL) {
                    b = next(b);
                    if (revee(b) == a) {
                        sum += info(b);
                        counter++;
                    }
                }
            }
            if (sum == 0 && counter == 0) {
                arr[tail].prodrat = 0;
                arr[tail].countrat = 0;
            } else {
                arr[tail].prodrat = float(sum) / float(counter);
                arr[tail].countrat = counter;
            }
            tail++;
        }
        //selection sort
        int choice;
        cout << "1. Ascending\n2. Descending\nYour choice -> ";
        cin >> choice;
        while (choice < 1 || choice > 2) {
            cout << "Invalid input\nYour choice -> ";
            cin >> choice;
        }
        cout << "\n-Product and average list-\n";
        if (choice == 1) {
            for (int i = 0; i < tail-1; i++) {
                int mini = i;
                for (int j = i+1; j < tail; j++) {
                    if (arr[j].prodrat <= arr[mini].prodrat) {
                        mini = j;
                    }
                }
                swap(arr[i], arr[mini]);
            }
        } else {
            for (int i = 0; i < tail-1; i++) {
                int maxi = i;
                for (int j = i+1; j < tail; j++) {
                    if (arr[j].prodrat >= arr[maxi].prodrat) {
                        maxi = j;
                    }
                }
                swap(arr[i], arr[maxi]);
            }
        }
        for (int i = 0; i < tail; i++) {
            cout << "- " << info(arr[i].prodinfo) << ", with average rating of " << arr[i].prodrat << " from " << arr[i].countrat << " review(s)\n";
        }
    } else {
        cout << "\nThere is currently no product right now\n";
    }
}

ptrcust searchCust(Customers C, string user, string password) {
    ptrcust ret = NULL, a = first(C);
    if (a != NULL) {
        if (user == user(a) && password == pass(a)) {
            ret = a;
        }
        while (next(a) != NULL && ret == NULL) {
            a = next(a);
            if (user == user(a) && password == pass(a)) {
                ret = a;
            }
        }
    }
    return ret;
}
ptrcust searchUser(Customers C, string user) {
    ptrcust ret = NULL, a = first(C);
    if (a != NULL) {
        if (user == user(a)) {
            ret = a;
        }
        while (next(a) != NULL && ret == NULL) {
            a = next(a);
            if (user == user(a)) {
                ret = a;
            }
        }
    }
    return ret;
}
ptrprod searchProd(Products P, string s) {
    ptrprod ret = NULL, a = first(P);
    if (a != NULL) {
        if (s == info(a)) {
            ret = a;
        }
        while (next(a) != NULL && ret == NULL) {
            a = next(a);
            if (s == info(a)) {
                    ret = a;
            }
        }
    }
    return ret;
}
ptrrev searchRev(Ratings R, string user, string prod) {
    ptrrev ret = NULL;
    ptrrev a = first(R);
    if (a != NULL) {
        if (user(rever(a)) == user && info(revee(a)) == prod) {
            ret = a;
        }
        while (next(a) != NULL && ret == NULL) {
            a = next(a);
            if (user(rever(a)) == user && info(revee(a)) == prod) {
                ret = a;
            }
        }
    }
    return ret;
}

void updateProfile(Customers C, ptrcust data) {
    int choice = -1;
    while (choice != 4) {
        anyKey();
        choice = -1;
        cout << "What would you want to update?\n1. Username\n2. Password\n3. Name\n4. Exit\n";
        cout << "Your choice -> "; cin >> choice;
        while (choice < 1 || choice > 4) {
            cout << "invalid choice\n";
            cout << "Your choice -> "; cin >> choice;
        }
        if (choice == 1) {
            string d;
            cout << "Current username : " << user(data) << "\n";
            cout << "New username : "; cin >> d;
            while (checkDuplicateNames(C, d)) {
                cout << "this username has already taken\n";
                cout << "New username : "; cin >> d;
            }
            user(data) = d;
            cout << "Your username has been changed\n";
        } else if (choice == 2) {
            cout << "Current password : " << pass(data) << "\n";
            cout << "New password : "; cin >> pass(data);
            cout << "Your password has been changed\n";
        } else if (choice == 3) {
            cout << "Current name : " << info(data) << "\n";
            cout << "New name : "; getline(cin >> ws, info(data));
            cout << "Your name has been changed\n";
        }
    }
}
void updateProd(Products &P) {
    ptrprod a = first(P);
    if (a == NULL) {
        cout << "There are currently no product to update right now\n";
    } else {
        string choice;
        while (choice != "-1") {
            anyKey();
            viewProd(P);
            cout << "Which product do you want to update?\ntype -1 if you are done\n";
            cout << "Product's name -> "; getline(cin >> ws, choice);
            while (searchProd(P, choice) == NULL && choice != "-1") {
                cout << "The name of the product does not exist\nPlease try again\n";
                cout << "Product's name -> "; getline(cin >> ws, choice);
            }
            if (searchProd(P, choice) != NULL && choice != "-1") {
                ptrprod a = searchProd(P, choice);
                string n;
                cout << "New product name -> "; getline(cin >> ws, n);
                while (searchProd(P, n) != NULL) {
                    cout << "This product name has already exist\n";
                    cout << "New product name -> ";
                    getline(cin >> ws, n);
                }
                info(a) = n;
                cout << "The product's name has been updated\n";
            }
        }
    }
}

void deleteProd(Products &P, Ratings &R) {
    if (first(P) != NULL) {
        viewProd(P);
        string choice;
        cout << "Which one do you want to delete?\nYour choice -> ";getline(cin >> ws, choice);
        while (searchProd(P, choice) == NULL) {
            cout << "Product does not exist\nYour choice -> ";
            getline(cin >> ws, choice);
        }
        ptrprod x = searchProd(P, choice);
        removeProd(P, x);
        // delete product's ratings
        ptrrev a = first(R), b;
        while (a != NULL) {
            if (revee(a) == x) {
                b = a;
                a = next(a);
                removeRev(R, b);
            } else {
                a = next(a);
            }
        }
        cout << "The product and all it's rating has been deleted\n";
    } else {
        cout << "There is no product to delete\n";
    }

}
void deleteCust(Customers &C, Ratings &R) {
    if (first(C) != NULL) {
        viewCust(C);
        string choice;
        cout << "Which one do you want to delete?\nYour choice -> ";getline(cin >> ws, choice);
        while (searchUser(C, choice) == NULL) {
            cout << "User does not exist\nYour choice -> ";
            getline(cin >> ws, choice);
        }
        ptrcust x = searchUser(C, choice);
        removeCust(C, x);
        // delete customer's ratings
        ptrrev a = first(R), b;
        while (a != NULL) {
            if (rever(a) == x) {
                b = a;
                a = next(a);
                removeRev(R, b);
            } else {
                a = next(a);
            }
        }
        cout << "The customer and all his/her product rating has been deleted\n";
    } else {
        cout << "There is no customer to delete\n";
    }
}
void deleteRev(Products P, Ratings &R, ptrcust c) {
    bool exist =  false;
    ptrrev a = first(R);
    if (a != NULL) {
        if (rever(a) == c) {
            exist = true;
        }
        while (next(a) != NULL && !exist) {
            a = next(a);
            if (rever(a) == c) {
                exist = true;
            }
        }
        if (exist) {
            string choice;
            viewRatedProd(R, c);
            cout << "Which one would you like to delete?\nYour choice -> ";
            getline(cin >> ws, choice);
            while (searchProd(P, choice) == NULL) {
                cout << "Product does not exist\nYour choice -> ";
                getline(cin >> ws, choice);
            }
            ptrrev x = searchRev(R, user(c), choice);
            removeRev(R, x);
            cout << "Rating has been deleted\n";
        } else {
            cout << "There is no rating to delete\n";
        }
    } else {
        cout << "There is no rating to delete\n";
    }
}

void removeRev(Ratings &R, ptrrev x) {
    if (x == first(R)) {
        first(R) = next(x);
    } else {
        ptrrev y = first(R);
        while (next(y) != x) {
            y = next(y);
        }
        next(y) = next(x);
    }
    next(x) = NULL;
}
void removeProd(Products &P, ptrprod x) {
    if (x == first(P)) {
        first(P) = next(x);
    } else {
        ptrprod y =  first(P);
        while (next(y) != x) {
            y = next(y);
        }
        next(y) = next(x);
    }
    next(x) = NULL;
}
void removeCust(Customers &C, ptrcust x) {
    if (x == first(C)) {
        first(C) = next(x);
    } else {
        ptrcust y =  first(C);
        while (next(y) != x) {
            y = next(y);
        }
        next(y) = next(x);
    }
    next(x) = NULL;
}
