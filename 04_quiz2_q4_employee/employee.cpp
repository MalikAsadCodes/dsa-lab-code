#include "employee.h"

node *create_node()
{
    node *n = new node;
    cout << "Enter name : ";
    cin >> n->name;
    cout << "Enter age : ";
    cin >> n->age;
    cout << "Enter salary : ";
    cin >> n->salary;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

void insert_begin(node *&head, int &count)
{
    node *n = create_node();

    // Check 1: list is empty, the node points to itself in both directions
    if (head == NULL)
    {
        n->next = n;
        n->prev = n;
        head = n;
        count++;
        return;
    }

    // Check 2: list is not empty, put the node before head
    node *last = head->prev;
    n->next = head;
    n->prev = last;
    last->next = n;
    head->prev = n;
    head = n;
    count++;
}

void insert_end(node *&head, int &count)
{
    node *n = create_node();

    // Check 1: list is empty
    if (head == NULL)
    {
        n->next = n;
        n->prev = n;
        head = n;
        count++;
        return;
    }

    // Check 2: list is not empty, put the node after the last node
    node *last = head->prev;
    n->next = head;
    n->prev = last;
    last->next = n;
    head->prev = n;
    count++;
}

void insert_pos(node *&head, int &count)
{
    int pos;
    cout << "Enter position (1 to " << count + 1 << ") : ";
    cin >> pos;

    // Check 1: position is out of range
    if (pos < 1 || pos > count + 1)
    {
        cout << "Invalid position" << endl;
        return;
    }

    // Check 2: first position
    if (pos == 1)
    {
        insert_begin(head, count);
        return;
    }

    // Check 3: position after the last node
    if (pos == count + 1)
    {
        insert_end(head, count);
        return;
    }

    // Check 4: middle, go to the node before the position
    node *n = create_node();
    node *p = head;
    for (int i = 1; i < pos - 1; i++)
        p = p->next;
    n->next = p->next;
    n->prev = p;
    p->next->prev = n;
    p->next = n;
    count++;
}

void display(node *head)
{
    if (head == NULL)
    {
        cout << "List is empty" << endl;
        return;
    }
    node *p = head;
    do
    {
        cout << p->name << "  " << p->age << "  " << p->salary << endl;
        p = p->next;
    } while (p != head);
}
