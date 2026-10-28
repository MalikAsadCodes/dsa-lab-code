#ifndef DSA_H
#define DSA_H

#include <iostream>
#include <string>
using namespace std;

const int MAXS = 100;   // most stacks / queues / circular queues of each kind

struct node
{
    int data;
    node *next;
};

struct func
{
    int maxsize = 6;    // nodes in every list

    // ----- stacks: stack i uses shead[i] and stop[i] -----
    node *shead[MAXS] = {NULL};
    node *stop[MAXS] = {NULL};
    int snum = 0;       // how many stacks exist
    int scur = 0;       // index of the selected stack

    // ----- queues: queue i uses qhead[i], qfront[i], qrear[i] -----
    node *qhead[MAXS] = {NULL};
    node *qfront[MAXS] = {NULL};
    node *qrear[MAXS] = {NULL};
    int qnum = 0;
    int qcur = 0;

    // ----- circular queues: circular i uses chead[i], cfront[i], crear[i] -----
    node *chead[MAXS] = {NULL};
    node *cfront[MAXS] = {NULL};
    node *crear[MAXS] = {NULL};
    int cnum = 0;
    int ccur = 0;

    // ----- temporary lists for palindrome, brackets and duplicates -----
    node *stmp = NULL;
    node *qtmp = NULL;
    node *ctmp = NULL;

    void createList(node *&head, int circular);
    node *prevNode(node *start, node *p);

    // ----- stack -----
    void push(node *head, node *&top, int x);
    int pop(node *head, node *&top);
    void display(node *head, node *top);
    int search(node *head, node *top, int x);
    int splitStack(node *head, node *top, node *&h1, node *&t1, node *&h2, node *&t2);
    void evenOdd(node *head, node *top, node *eh, node *&et, node *oh, node *&ot);
    void nextGreater(node *head, node *top);
    void sortList(node *head, node *top);
    int isPalindrome(string s);
    void copyStack(node *head, node *top, node *ch, node *&ct);
    int isBalanced(string s);
    void removeDuplicates(node *head, node *&top);
    void intersection(node *h1, node *t1, node *h2, node *t2, node *rh, node *&rt);

    // ----- queue -----
    void qpush(node *head, node *&f, node *&r, int x);
    int qpop(node *&head, node *&f, node *&r);
    void qdisplay(node *f, node *r);
    int qcount(node *f, node *r);
    int qsearch(node *f, node *r, int x);
    void qreverse(node *f, node *r);
    int qpopLast(node *&f, node *&r);
    int splitQueue(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2);
    void qevenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR);
    void qnextGreater(node *f, node *r);
    void qsortList(node *f, node *r);
    int qisPalindrome(string s);
    void copyQueue(node *f, node *r, node *ch, node *&cf, node *&cr);
    int qisBalanced(string s);
    void qremoveDuplicates(node *&head, node *&f, node *&r);
    void qintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr);

    // ----- circular queue -----
    void cpush(node *head, node *&f, node *&r, int x);
    int cpop(node *&f, node *&r);
    void cdisplay(node *f, node *r);
    int ccount(node *f, node *r);
    int csearch(node *f, node *r, int x);
    void creverse(node *f, node *r);
    int cpopLast(node *&f, node *&r);
    int splitCircular(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2);
    void cevenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR);
    void cnextGreater(node *f, node *r);
    void csortList(node *f, node *r);
    int cisPalindrome(string s);
    void copyCircular(node *f, node *r, node *ch, node *&cf, node *&cr);
    int cisBalanced(string s);
    void cremoveDuplicates(node *head, node *&f, node *&r);
    void cintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr);

    // ----- menus -----
    void stackMenu();
    void queueMenu();
    void circularMenu();
    void menu();
};

#endif
