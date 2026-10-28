#include "stack.h"

void push(node *&top, char c)
{
    node *n = new node;      // dynamic: a new node for every push
    n->data = c;
    n->next = top;
    top = n;
}

char pop(node *&top)
{
    // Check 1: stack is empty
    if (top == NULL)
    {
        cout << "Stack Underflow" << endl;
        return '\0';
    }
    node *t = top;
    char c = t->data;
    top = top->next;
    delete t;
    return c;
}
