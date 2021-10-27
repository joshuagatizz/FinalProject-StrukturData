#define first(a) a.first
#define next(a) a->next
#define info(a) a->info
#define rever(a) a->rever
#define revee(a) a->revee
#define user(a) a->user
#define pass(a) a->pass
#include <bits/stdc++.h>
using namespace std;

// POINTERS
typedef struct elmProd *ptrprod;
typedef struct elmCust *ptrcust;
typedef struct elmRev *ptrrev;

// STRUCTS
struct elmProd {
    string info;
    ptrprod next;
};
struct elmCust {
    string info, user, pass;
    ptrcust next;
};
struct elmRev {
    int info;
    ptrcust rever;
    ptrprod revee;
    ptrrev next;
};
struct Products {
    ptrprod first;
};
struct Customers {
    ptrcust first;
};
struct Ratings {
    ptrrev first;
};


// MENUS & GENERAL
void anyKey();
void initialize(Products &P, Customers &C, Ratings &R);
void mainMenu();
void adminContext();
void adminMenu(Products &P, Customers &C, Ratings &R);
void custContext();
void custMenu(Products &P, Customers &C, Ratings &R);
void nonCustContext();
void nonCustMenu(Products &P, Customers &C, Ratings &R);

// LOGIN & SIGNUP
void logInAdm(Customers C, ptrcust &data);
void logInCust(Customers C, ptrcust &data);
void signUp(Customers &C);

// ADD
void addProd(Products &P);
void addRating(Products &P, ptrcust &c, Ratings &R);

// DUPLICATE
bool checkDuplicateProd(Products P, string name);
bool checkDuplicateNames(Customers C, string s);

//CREATE
ptrrev createRev(Ratings &R, int rat, ptrprod a, ptrcust b);
ptrcust createCust(string name, string user, string pass);
ptrprod createProd(string name);

// VIEW
void viewCust(Customers C);
void viewProd(Products P);
void viewRatByProd(Ratings R, Products P);
void viewRatByCust(Ratings R, Customers C);
void viewRatedProd(Ratings R, ptrcust c);
void viewUnratedProd(Products P, Ratings R, ptrcust c);
void viewProductAndRating(Products P, Ratings R);

// SEARCH
ptrcust searchCust(Customers C, string user, string password);
ptrprod searchProd(Products P, string s);
ptrcust searchUser(Customers C, string user);
ptrrev searchRev(Ratings R, string user, string prod);

//UPDATE
void updateProd(Products &P);
void updateProfile(Customers C, ptrcust data);

// DELETE & REMOVE
void deleteProd(Products &P, Ratings &R);
void deleteCust(Customers &C, Ratings &R);
void removeProd(Products &P, ptrprod x);
void removeCust(Customers &C, ptrcust x);
void deleteRev(Products P, Ratings &R, ptrcust c);
void removeRev(Ratings &R, ptrrev x);
