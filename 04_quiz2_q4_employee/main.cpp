#include "employee.h"

int main()
{
    node *head = NULL;
    int count = 0;
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "1. Insert at beginning" << endl;
        cout << "2. Insert at end" << endl;
        cout << "3. Insert at position" << endl;
        cout << "4. Display" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice : ";
        cin >> choice;

        if (choice == 1)
            insert_begin(head, count);
        else if (choice == 2)
            insert_end(head, count);
        else if (choice == 3)
            insert_pos(head, count);
        else if (choice == 4)
            display(head);
    }
    return 0;
}
