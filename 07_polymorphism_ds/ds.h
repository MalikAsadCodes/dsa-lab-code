#ifndef DS_H
#define DS_H

#include <iostream>
#include <string>
using namespace std;

const int MAXS = 100;   // most lists (or arrays) one structure can keep
const int ASIZE = 10;   // values in every array

// ----- node for every int structure (singly lists do not use prev) -----
struct node
{
    int data;
    node *next;         // link to the node after
    node *prev;         // link to the node before
};

// ----- node for student records (Q9 and Q10) -----
struct student
{
    int rollno;
    string name;
    int marks[3];
    student *next;
    student *prev;
};

// ----- node for one polynomial term (only Q8) -----
struct term
{
    int coef;           // coefficient
    int exp;            // power of x
    term *next;
};

// =====================================================
// BASE struct: every data structure has these operations.
// "= 0" means the base has no code, every derived struct writes its own.
// =====================================================
struct ds
{
    virtual void insert() = 0;
    virtual void del() = 0;
    virtual void search() = 0;
    virtual void reverse() = 0;
    virtual void count() = 0;
    virtual void display() = 0;
    virtual void menu() = 0;
};

// =====================================================
// 1. ARRAY: array i is a[i] and holds n[i] values
// =====================================================
struct arrayDS : public ds
{
    int a[MAXS][ASIZE];
    int n[MAXS] = {0};  // values in every array
    int num = 0;        // how many arrays exist
    int cur = 0;        // index of the selected array

    // ----- the 7 virtual functions -----
    void insert();
    void del();
    void search();
    void reverse();
    void count();
    void display();
    void menu();

    // ----- basic function -----
    void displayArray(int A[], int m);

    // ----- extra questions -----
    int countOccur(int A[], int m, int x);
    void maxMinTotal(int A[], int m);
    int mergeSorted(int A[], int na, int B[], int nb, int C[], int &nc);
};

// =====================================================
// 2. SINGLY LINKED LIST: list i starts at head[i]
// =====================================================
struct singlyList : public ds
{
    node *head[MAXS] = {NULL};
    int num = 0;        // how many lists exist
    int cur = 0;        // index of the selected list

    // ----- the 7 virtual functions -----
    void insert();
    void del();
    void search();
    void reverse();
    void count();
    void display();
    void menu();

    // ----- basic functions -----
    void insertBeg(node *&h, int x);
    void insertPos(node *&h, int pos, int x);
    void insertEnd(node *&h, int x);
    int delBeg(node *&h);
    int delPos(node *&h, int pos);
    int delEnd(node *&h);
    int delValue(node *&h, int x);
    int countList(node *h);
    void displayList(node *h);

    // ----- lab questions Q1 to Q8 -----
    void concatenate(node *&h1, node *&h2);
    int splitList(node *h1, node *&h2);
    int countOccur(node *h, int x);
    void maxMinTotal(node *h);
    void evenOdd(node *&h1, node *&h2, node *&h3);
    void digitList(node *&h, int number);
    void mergeSorted(node *h1, node *h2, node *&h3);
    void insertTerm(term *&h, int c, int e);
    void displayPoly(term *h);
    void multiplyPoly(term *p1, term *p2, term *&res);
};

// =====================================================
// MAIN MENU: all[i] is a BASE pointer to one derived struct
// =====================================================
struct func
{
    ds *all[9] = {NULL};
    void menu();
};

#endif
