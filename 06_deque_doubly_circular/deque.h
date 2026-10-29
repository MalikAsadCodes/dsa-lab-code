#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <string>
using namespace std;

const int MAXS = 100;   // most deques that can exist

struct node
{
    int data;
    node *next;         // link to the node after
    node *prev;         // link to the node before
};

struct func
{
    int maxsize = 10;   // nodes in every deque

    // ----- deques: deque i uses dhead[i], dfront[i], drear[i] -----
    node *dhead[MAXS] = {NULL};
    node *dfront[MAXS] = {NULL};
    node *drear[MAXS] = {NULL};
    int dnum = 0;       // how many deques exist
    int dcur = 0;       // index of the selected deque

    // ----- temporary deque for palindrome, brackets and duplicates -----
    node *dtmp = NULL;

    void createList(node *&head);

    // ----- deque on a doubly circular list -----
    void dpushFront(node *head, node *&f, node *&r, int x);
    void dpushRear(node *head, node *&f, node *&r, int x);
    int dpopFront(node *head, node *&f, node *&r);
    int dpopRear(node *head, node *&f, node *&r);
    void ddisplay(node *f, node *r);
    void ddisplayBack(node *f, node *r);
    int dcount(node *f, node *r);
    int dsearch(node *f, node *r, int x);
    void dreverse(node *&f, node *&r);

    // ----- lab questions Q1 to Q10 -----
    int splitDeque(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2);
    void devenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR);
    void dnextGreater(node *f, node *r);
    void dsortList(node *f, node *r);
    int disPalindrome(string s);
    void copyDeque(node *f, node *r, node *ch, node *&cf, node *&cr);
    int disBalanced(string s);
    void dremoveDuplicates(node *head, node *&f, node *&r);
    void dintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr);

    // ----- group questions: each one makes a NEW deque, the original is not changed -----
    // the int ones return 1 when the new deque is made, 0 when the input is wrong
    int dreversePairs(node *f, node *r, int k, node *&nh, node *&nf, node *&nr);
    int dsumPairs(node *f, node *r, int k, node *&nh, node *&nf, node *&nr);
    int dmaxMinPairs(node *f, node *r, int k, node *&bh, node *&bf, node *&br, node *&sh, node *&sf, node *&sr);
    void ddeleteGreater(node *f, node *r, node *&nh, node *&nf, node *&nr);

    // ----- pairs with a given sum (only prints, nothing is changed) -----
    void dfindPairs(node *f, node *r, int sum);

    // ----- menus -----
    void dequeMenu();
    void menu();
};

#endif
