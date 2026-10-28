#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <string>
using namespace std;

struct node
{
    string name;
    int age;
    float salary;
    node *next;
    node *prev;
};

node *create_node();
void insert_begin(node *&head, int &count);
void insert_end(node *&head, int &count);
void insert_pos(node *&head, int &count);
void display(node *head);        // extra: only to see the result in main

#endif
