#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
using namespace std;

struct node
{
    char data;
    node *next;
};

void push(node *&top, char c);
char pop(node *&top);

#endif
