#include "ds.h"

// =====================================================
// ===================== MAIN MENU =====================
// =====================================================
// all[i] is a pointer to the BASE struct ds, but it points to a DERIVED struct.
// all[c]->menu() runs the menu of the structure that was chosen (polymorphism).

void func::menu()
{
    int ch = 0;
    all[0] = new arrayDS;
    all[1] = new singlyList;
    // the next days add the other structures here

    do
    {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Array" << endl;
        cout << "2. Singly linked list" << endl;
        cout << "3. Singly circular linked list (students)" << endl;
        cout << "4. Doubly linked list" << endl;
        cout << "5. Doubly circular linked list (students)" << endl;
        cout << "6. Stack" << endl;
        cout << "7. Queue" << endl;
        cout << "8. Circular queue" << endl;
        cout << "9. Deque" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> ch;

        if (ch >= 1 && ch <= 9)
        {
            // Check 1: this structure is not added yet
            if (all[ch - 1] == NULL)
                cout << "This structure comes in the next stage" << endl;
            else
                all[ch - 1]->menu();
        }
        else if (ch != 0)
            cout << "Wrong choice" << endl;
    } while (ch != 0);
}

// =====================================================
// ====================== 1. ARRAY =====================
// =====================================================
// Array i is a[i] and holds n[i] values (at most ASIZE).
// The array is the only structure where overflow is found with a count: n == ASIZE.

// ---------- Display any array ----------
void arrayDS::displayArray(int A[], int m)
{
    if (m == 0)
    {
        cout << "empty" << endl;
        return;
    }
    for (int i = 0; i < m; i++)
        cout << A[i] << " ";
    cout << endl;
}

// ---------- Insert (beginning / position / end) ----------
void arrayDS::insert()
{
    int *A = a[cur];        // the selected array
    int &m = n[cur];        // values in it
    int c = 0, pos = 0, x = 0;

    // Check 1: array is full
    if (m == ASIZE)
    {
        cout << "Array Overflow" << endl;
        return;
    }

    cout << "1. At beginning  2. At position  3. At end" << endl;
    cout << "Choice: ";
    cin >> c;
    if (c == 1)
        pos = 1;
    else if (c == 2)
    {
        cout << "Position (1 to " << m + 1 << "): ";
        cin >> pos;
    }
    else if (c == 3)
        pos = m + 1;

    // Check 2: wrong choice or wrong position (pos stays 0 on a wrong choice)
    if (pos < 1 || pos > m + 1)
    {
        cout << "Wrong choice or position" << endl;
        return;
    }

    cout << "Value: ";
    cin >> x;

    // move every value from pos to the end one place right, starting from the end
    for (int i = m; i >= pos; i--)
        A[i] = A[i - 1];
    A[pos - 1] = x;         // position 1 is index 0
    m++;
}

// ---------- Delete (beginning / position / end / by value) ----------
void arrayDS::del()
{
    int *A = a[cur];
    int &m = n[cur];
    int c = 0, pos = 0, x = 0;

    // Check 1: array is empty
    if (m == 0)
    {
        cout << "Array Underflow" << endl;
        return;
    }

    cout << "1. From beginning  2. From position  3. From end  4. By value" << endl;
    cout << "Choice: ";
    cin >> c;
    if (c == 1)
        pos = 1;
    else if (c == 2)
    {
        cout << "Position (1 to " << m << "): ";
        cin >> pos;
    }
    else if (c == 3)
        pos = m;
    else if (c == 4)
    {
        cout << "Value: ";
        cin >> x;
        // pos = the first place where x is found
        for (int i = 0; i < m; i++)
        {
            if (A[i] == x)
            {
                pos = i + 1;
                break;
            }
        }
        // Check 2: value is not in the array
        if (pos == 0)
        {
            cout << x << " not found" << endl;
            return;
        }
    }

    // Check 3: wrong choice or wrong position
    if (pos < 1 || pos > m)
    {
        cout << "Wrong choice or position" << endl;
        return;
    }

    cout << "Deleted: " << A[pos - 1] << endl;
    // move every value after pos one place left
    for (int i = pos - 1; i < m - 1; i++)
        A[i] = A[i + 1];
    m--;
}

// ---------- Search ----------
void arrayDS::search()
{
    int x = 0;

    // Check 1: array is empty
    if (n[cur] == 0)
    {
        cout << "Array is empty, insert some values first" << endl;
        return;
    }

    cout << "Value to search: ";
    cin >> x;
    for (int i = 0; i < n[cur]; i++)
    {
        if (a[cur][i] == x)
        {
            cout << x << " found at position " << i + 1 << endl;
            return;
        }
    }
    cout << x << " not found" << endl;
}

// ---------- Reverse ----------
void arrayDS::reverse()
{
    int *A = a[cur];
    int m = n[cur];
    int t;

    // Check 1: array is empty
    if (m == 0)
    {
        cout << "Array is empty, insert some values first" << endl;
        return;
    }

    // swap first with last, second with second-last, ... up to the middle
    for (int i = 0; i < m / 2; i++)
    {
        t = A[i];
        A[i] = A[m - 1 - i];
        A[m - 1 - i] = t;
    }
}

// ---------- Count ----------
void arrayDS::count()
{
    cout << "Count: " << n[cur] << endl;
}

// ---------- Display the selected array ----------
void arrayDS::display()
{
    cout << "Array " << cur + 1 << ": ";
    displayArray(a[cur], n[cur]);
}

// ---------- Count occurrences of x ----------
int arrayDS::countOccur(int A[], int m, int x)
{
    int c = 0;
    for (int i = 0; i < m; i++)
    {
        if (A[i] == x)
            c++;
    }
    return c;
}

// ---------- Largest, smallest, total and average ----------
void arrayDS::maxMinTotal(int A[], int m)
{
    // Check 1: array is empty
    if (m == 0)
    {
        cout << "Array is empty, insert some values first" << endl;
        return;
    }

    int big = A[0];         // start with the first value
    int small = A[0];
    int total = 0;
    for (int i = 0; i < m; i++)
    {
        if (A[i] > big)
            big = A[i];
        if (A[i] < small)
            small = A[i];
        total = total + A[i];
    }
    double avg = (double)total / m;     // double, so 7 / 2 gives 3.5

    cout << "Largest: " << big << endl;
    cout << "Smallest: " << small << endl;
    cout << "Total: " << total << endl;
    cout << "Average: " << avg << endl;
}

// ---------- Merge two sorted arrays into a third sorted array ----------
// A value that is in both arrays goes in only once.
// Returns 1 when the new array is made, 0 when it needs more than ASIZE values.
int arrayDS::mergeSorted(int A[], int na, int B[], int nb, int C[], int &nc)
{
    int i = 0, j = 0;
    nc = 0;

    // both arrays still have values: take the smaller one
    while (i < na && j < nb && nc < ASIZE)
    {
        if (A[i] < B[j])
        {
            C[nc] = A[i];
            i++;
        }
        else if (B[j] < A[i])
        {
            C[nc] = B[j];
            j++;
        }
        else                // same value in both: take it once
        {
            C[nc] = A[i];
            i++;
            j++;
        }
        nc++;
    }

    // copy what is left in A, then what is left in B
    while (i < na && nc < ASIZE)
    {
        C[nc] = A[i];
        i++;
        nc++;
    }
    while (j < nb && nc < ASIZE)
    {
        C[nc] = B[j];
        j++;
        nc++;
    }

    // Check 1: values are still left, so the new array is too small
    if (i < na || j < nb)
    {
        cout << "Array Overflow: the merged array needs more than " << ASIZE << " values" << endl;
        nc = 0;
        return 0;
    }
    return 1;
}

// ---------- Array menu ----------
void arrayDS::menu()
{
    int ch = 0, x = 0, k = 0;
    if (num == 0)
        num = 1;            // start with array 1 (empty)

    do
    {
        cout << "\n--- ARRAY " << cur + 1 << " (of " << num << ") ---" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Reverse" << endl;
        cout << "5. Count" << endl;
        cout << "6. Display" << endl;
        cout << "7. Count occurrences of a value" << endl;
        cout << "8. Largest, smallest, total, average" << endl;
        cout << "9. Merge two sorted arrays (adds 1 new array)" << endl;
        cout << "10. Create a new array" << endl;
        cout << "11. Select an array" << endl;
        cout << "12. Show all arrays" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            insert();
            display();
            break;

        case 2:
            del();
            display();
            break;

        case 3:
            search();
            break;

        case 4:
            reverse();
            display();
            break;

        case 5:
            count();
            break;

        case 6:
            display();
            break;

        case 7:
            cout << "Value: ";
            cin >> x;
            cout << x << " comes " << countOccur(a[cur], n[cur], x) << " time(s)" << endl;
            break;

        case 8:
            display();
            maxMinTotal(a[cur], n[cur]);
            break;

        case 9:
        {
            int p = 0, q = 0;
            cout << "First sorted array (1 to " << num << "): ";
            cin >> p;
            cout << "Second sorted array (1 to " << num << "): ";
            cin >> q;

            // Check 1: both numbers must be arrays that exist
            if (p < 1 || p > num || q < 1 || q > num)
            {
                cout << "Wrong array number" << endl;
                break;
            }
            // Check 2: the two arrays must be different
            if (p == q)
            {
                cout << "Choose two different arrays" << endl;
                break;
            }
            // Check 3: room for the result array
            if (num + 1 > MAXS)
            {
                cout << "No room for another array" << endl;
                break;
            }
            p--;                    // user numbers start at 1, the array at 0
            q--;

            int c = num;            // the result goes in a new array
            if (mergeSorted(a[p], n[p], a[q], n[q], a[c], n[c]) == 0)
                break;              // too many values, no array was made
            num++;

            cout << "Array " << p + 1 << ": ";
            displayArray(a[p], n[p]);
            cout << "Array " << q + 1 << ": ";
            displayArray(a[q], n[q]);
            cout << "Merged (array " << c + 1 << "): ";
            displayArray(a[c], n[c]);
            break;
        }

        case 10:
            if (num >= MAXS)
            {
                cout << "No room for another array" << endl;
                break;
            }
            n[num] = 0;
            cur = num;              // the new array becomes the selected one
            num++;
            cout << "Array " << cur + 1 << " created and selected" << endl;
            break;

        case 11:
            cout << "Array number (1 to " << num << "): ";
            cin >> k;
            if (k < 1 || k > num)
                cout << "Wrong array number" << endl;
            else
            {
                cur = k - 1;
                display();
            }
            break;

        case 12:
            for (int i = 0; i < num; i++)
            {
                cout << "Array " << i + 1 << ": ";
                displayArray(a[i], n[i]);
            }
            break;

        case 0:
            break;

        default:
            cout << "Wrong choice" << endl;
        }
    } while (ch != 0);
}

// =====================================================
// ================ 2. SINGLY LINKED LIST ==============
// =====================================================
// List i starts at head[i]. Nodes are made with new and removed with delete.
// The last node's next is NULL. prev is not used here.

// ---------- Insert at beginning ----------
void singlyList::insertBeg(node *&h, int x)
{
    node *t = new node;
    t->data = x;
    t->next = h;            // new node -> old first node
    h = t;                  // new node is the first node
}

// ---------- Insert at position (1 = beginning) ----------
// The caller checks that pos is from 1 to count + 1.
void singlyList::insertPos(node *&h, int pos, int x)
{
    // Check 1: position 1 is the beginning
    if (pos == 1)
    {
        insertBeg(h, x);
        return;
    }

    node *p = h;
    // p goes to the node before the position
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    node *t = new node;
    t->data = x;
    t->next = p->next;
    p->next = t;
}

// ---------- Insert at end ----------
void singlyList::insertEnd(node *&h, int x)
{
    node *t = new node;
    t->data = x;
    t->next = NULL;         // the new node is the last node

    // Check 1: empty list, the new node is the first node
    if (h == NULL)
    {
        h = t;
        return;
    }

    node *p = h;
    while (p->next != NULL)     // p goes to the last node
        p = p->next;
    p->next = t;
}

// ---------- Delete from beginning (the caller checks the list is not empty) ----------
int singlyList::delBeg(node *&h)
{
    node *p = h;
    int x = p->data;
    h = h->next;            // the second node is the first node now
    delete p;
    return x;
}

// ---------- Delete at position (the caller checks pos is from 1 to count) ----------
int singlyList::delPos(node *&h, int pos)
{
    // Check 1: position 1 is the beginning
    if (pos == 1)
        return delBeg(h);

    node *p = h;
    // p goes to the node before the position
    for (int i = 1; i < pos - 1; i++)
        p = p->next;

    node *q = p->next;      // q is the node to delete
    int x = q->data;
    p->next = q->next;      // jump over q
    delete q;
    return x;
}

// ---------- Delete from end (the caller checks the list is not empty) ----------
int singlyList::delEnd(node *&h)
{
    int x;

    // Check 1: only one node, the list becomes empty
    if (h->next == NULL)
    {
        x = h->data;
        delete h;
        h = NULL;
        return x;
    }

    node *p = h;
    while (p->next->next != NULL)   // p goes to the second-last node
        p = p->next;

    x = p->next->data;
    delete p->next;
    p->next = NULL;         // p is the last node now
    return x;
}

// ---------- Delete by value (first one found) ----------
// Returns 1 when x is deleted, 0 when x is not in the list.
int singlyList::delValue(node *&h, int x)
{
    // Check 1: x is in the first node
    if (h->data == x)
    {
        delBeg(h);
        return 1;
    }

    node *p = h;
    // p stops at the node before x
    while (p->next != NULL && p->next->data != x)
        p = p->next;

    // Check 2: end of list reached, x is not found
    if (p->next == NULL)
        return 0;

    node *q = p->next;
    p->next = q->next;
    delete q;
    return 1;
}

// ---------- Count any list ----------
int singlyList::countList(node *h)
{
    int c = 0;
    node *p = h;
    while (p != NULL)
    {
        c++;
        p = p->next;
    }
    return c;
}

// ---------- Display any list ----------
void singlyList::displayList(node *h)
{
    if (h == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = h;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

// ---------- Insert (virtual: beginning / position / end) ----------
void singlyList::insert()
{
    node *&h = head[cur];   // head of the selected list
    int c = 0, pos = 0, x = 0;

    cout << "1. At beginning  2. At position  3. At end" << endl;
    cout << "Choice: ";
    cin >> c;

    // Check 1: wrong choice
    if (c < 1 || c > 3)
    {
        cout << "Wrong choice" << endl;
        return;
    }

    if (c == 2)
    {
        cout << "Position (1 to " << countList(h) + 1 << "): ";
        cin >> pos;
        // Check 2: position must be from 1 to count + 1
        if (pos < 1 || pos > countList(h) + 1)
        {
            cout << "Wrong position" << endl;
            return;
        }
    }

    cout << "Value: ";
    cin >> x;
    if (c == 1)
        insertBeg(h, x);
    else if (c == 2)
        insertPos(h, pos, x);
    else
        insertEnd(h, x);
}

// ---------- Delete (virtual: beginning / position / end / by value) ----------
void singlyList::del()
{
    node *&h = head[cur];
    int c = 0, pos = 0, x = 0;

    // Check 1: list is empty
    if (h == NULL)
    {
        cout << "List Underflow" << endl;
        return;
    }

    cout << "1. From beginning  2. From position  3. From end  4. By value" << endl;
    cout << "Choice: ";
    cin >> c;

    switch (c)
    {
    case 1:
        cout << "Deleted: " << delBeg(h) << endl;
        break;

    case 2:
        cout << "Position (1 to " << countList(h) << "): ";
        cin >> pos;
        // Check 2: position must be from 1 to count
        if (pos < 1 || pos > countList(h))
            cout << "Wrong position" << endl;
        else
            cout << "Deleted: " << delPos(h, pos) << endl;
        break;

    case 3:
        cout << "Deleted: " << delEnd(h) << endl;
        break;

    case 4:
        cout << "Value: ";
        cin >> x;
        if (delValue(h, x) == 1)
            cout << x << " deleted" << endl;
        else
            cout << x << " not found" << endl;
        break;

    default:
        cout << "Wrong choice" << endl;
    }
}

// ---------- Search (virtual) ----------
void singlyList::search()
{
    int x = 0, pos = 1;

    // Check 1: list is empty
    if (head[cur] == NULL)
    {
        cout << "List is empty, insert some values first" << endl;
        return;
    }

    cout << "Value to search: ";
    cin >> x;
    node *p = head[cur];
    while (p != NULL)
    {
        if (p->data == x)
        {
            cout << x << " found at position " << pos << endl;
            return;
        }
        p = p->next;
        pos++;
    }
    cout << x << " not found" << endl;
}

// ---------- Reverse (virtual: turn every next link back) ----------
void singlyList::reverse()
{
    node *&h = head[cur];

    // Check 1: list is empty
    if (h == NULL)
    {
        cout << "List is empty, insert some values first" << endl;
        return;
    }

    node *b = NULL;         // node before p (already reversed part)
    node *p = h;            // node being turned
    node *q;                // node after p
    while (p != NULL)
    {
        q = p->next;        // remember the next node
        p->next = b;        // turn the link back
        b = p;
        p = q;
    }
    h = b;                  // the old last node is the first node
}

// ---------- Count (virtual) ----------
void singlyList::count()
{
    cout << "Count: " << countList(head[cur]) << endl;
}

// ---------- Display (virtual) ----------
void singlyList::display()
{
    cout << "List " << cur + 1 << ": ";
    displayList(head[cur]);
}

// ---------- Q1: concatenate, list B goes at the end of list A ----------
// Done with pointers: A's last node -> B's first node. B becomes empty.
void singlyList::concatenate(node *&h1, node *&h2)
{
    // Check 1: A is empty, so A simply takes B's nodes
    if (h1 == NULL)
    {
        h1 = h2;
        h2 = NULL;
        return;
    }

    node *p = h1;
    while (p->next != NULL)     // p goes to A's last node
        p = p->next;
    p->next = h2;           // A's last node -> B's first node
    h2 = NULL;              // B's nodes belong to A now
}

// ---------- Q2: split into two lists ----------
// The first k = (n + 1) / 2 values stay in h1, the rest go to the new list h2.
// Returns 1 when split, 0 when there are fewer than 2 values.
int singlyList::splitList(node *h1, node *&h2)
{
    int n = countList(h1);

    // Check 1: a split needs at least 2 values
    if (n < 2)
    {
        cout << "List needs at least 2 values to split" << endl;
        return 0;
    }

    int k = (n + 1) / 2;    // half of the values, rounded up
    node *p = h1;
    for (int i = 1; i < k; i++)     // p goes to the k-th node
        p = p->next;

    h2 = p->next;           // the second list starts after p
    p->next = NULL;         // the first list ends at p
    return 1;
}

// ---------- Q3: count occurrences of x ----------
int singlyList::countOccur(node *h, int x)
{
    int c = 0;
    node *p = h;
    while (p != NULL)
    {
        if (p->data == x)
            c++;
        p = p->next;
    }
    return c;
}

// ---------- Q4: largest, smallest, total and average ----------
void singlyList::maxMinTotal(node *h)
{
    // Check 1: list is empty
    if (h == NULL)
    {
        cout << "List is empty, insert some values first" << endl;
        return;
    }

    int big = h->data;      // start with the first value
    int small = h->data;
    int total = 0;
    int c = 0;              // values in the list, for the average
    node *p = h;
    while (p != NULL)
    {
        if (p->data > big)
            big = p->data;
        if (p->data < small)
            small = p->data;
        total = total + p->data;
        c++;
        p = p->next;
    }
    double avg = (double)total / c;     // double, so 7 / 2 gives 3.5

    cout << "Largest: " << big << endl;
    cout << "Smallest: " << small << endl;
    cout << "Total: " << total << endl;
    cout << "Average: " << avg << endl;
}

// ---------- Q5: even nodes of L1 go to L2, odd nodes go to L3 ----------
// Nodes are moved with pointers (no new nodes), so L1 ends empty.
// L2 and L3 may already have values; the moved nodes go at their end.
void singlyList::evenOdd(node *&h1, node *&h2, node *&h3)
{
    node *e2 = h2;          // last node of L2
    node *e3 = h3;          // last node of L3

    // e2 and e3 go to the last nodes (only if the list is not empty)
    if (e2 != NULL)
    {
        while (e2->next != NULL)
            e2 = e2->next;
    }
    if (e3 != NULL)
    {
        while (e3->next != NULL)
            e3 = e3->next;
    }

    node *p;
    while (h1 != NULL)
    {
        p = h1;             // take the first node out of L1
        h1 = h1->next;
        p->next = NULL;

        if (p->data % 2 == 0)
        {
            // Check 1: L2 is empty, p is its first node
            if (h2 == NULL)
                h2 = p;
            else
                e2->next = p;
            e2 = p;         // p is L2's last node now
        }
        else
        {
            // Check 2: L3 is empty, p is its first node
            if (h3 == NULL)
                h3 = p;
            else
                e3->next = p;
            e3 = p;
        }
    }
}

// ---------- Q6: list from the digits of a number ----------
// 54681 % 10 gives 1, then 8, 6, 4, 5 (last digit first).
// Inserting each digit at the BEGINNING puts them back in order: 5 4 6 8 1
void singlyList::digitList(node *&h, int number)
{
    // Check 1: the number 0 has one digit
    if (number == 0)
    {
        insertBeg(h, 0);
        return;
    }

    while (number > 0)
    {
        insertBeg(h, number % 10);  // last digit
        number = number / 10;       // remove the last digit
    }
}

// ---------- Q7: merge two sorted lists into a third sorted list ----------
// The two lists do not change. A value that is in both goes in only once.
void singlyList::mergeSorted(node *h1, node *h2, node *&h3)
{
    node *p = h1;
    node *q = h2;

    // both lists still have values: take the smaller one
    while (p != NULL && q != NULL)
    {
        if (p->data < q->data)
        {
            insertEnd(h3, p->data);
            p = p->next;
        }
        else if (q->data < p->data)
        {
            insertEnd(h3, q->data);
            q = q->next;
        }
        else                // same value in both: insert it once
        {
            insertEnd(h3, p->data);
            p = p->next;
            q = q->next;
        }
    }

    // copy what is left in the first list, then in the second list
    while (p != NULL)
    {
        insertEnd(h3, p->data);
        p = p->next;
    }
    while (q != NULL)
    {
        insertEnd(h3, q->data);
        q = q->next;
    }
}

// ---------- Q8: insert a term, the list stays in falling order of power ----------
// If a term with the same power is already there, the coefficients are added.
void singlyList::insertTerm(term *&h, int c, int e)
{
    term *p = h;

    // Check 1: same power already in the list, add the coefficient
    while (p != NULL)
    {
        if (p->exp == e)
        {
            p->coef = p->coef + c;
            return;
        }
        p = p->next;
    }

    term *t = new term;
    t->coef = c;
    t->exp = e;

    // Check 2: list is empty, or the new power is the biggest: insert at the beginning
    if (h == NULL || e > h->exp)
    {
        t->next = h;
        h = t;
        return;
    }

    p = h;
    // p stops at the last term whose power is bigger than e
    while (p->next != NULL && p->next->exp > e)
        p = p->next;
    t->next = p->next;
    p->next = t;
}

// ---------- Q8: display a polynomial, like 6x^3 + 4x^1 + 2x^0 ----------
void singlyList::displayPoly(term *h)
{
    if (h == NULL)
    {
        cout << "0" << endl;
        return;
    }
    term *p = h;
    while (p != NULL)
    {
        cout << p->coef << "x^" << p->exp;
        if (p->next != NULL)
            cout << " + ";
        p = p->next;
    }
    cout << endl;
}

// ---------- Q8: multiply two polynomials ----------
// Every term of p1 is multiplied with every term of p2:
// coefficients are multiplied, powers are added.
void singlyList::multiplyPoly(term *p1, term *p2, term *&res)
{
    term *p = p1;
    term *q;
    while (p != NULL)
    {
        q = p2;
        while (q != NULL)
        {
            insertTerm(res, p->coef * q->coef, p->exp + q->exp);
            q = q->next;
        }
        p = p->next;
    }
}

// ---------- Singly linked list menu ----------
void singlyList::menu()
{
    int ch = 0, x = 0, k = 0, p = 0, q = 0, r = 0;
    if (num == 0)
        num = 1;            // start with list 1 (empty)

    do
    {
        cout << "\n--- SINGLY LINKED LIST " << cur + 1 << " (of " << num << ") ---" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Search" << endl;
        cout << "4. Reverse" << endl;
        cout << "5. Count" << endl;
        cout << "6. Display" << endl;
        cout << "7. Q1 Concatenate two lists" << endl;
        cout << "8. Q2 Split into two lists (adds 1 new list)" << endl;
        cout << "9. Q3 Count occurrences of a value" << endl;
        cout << "10. Q4 Largest, smallest, total, average" << endl;
        cout << "11. Q5 Even nodes of L1 to L2, odd nodes to L3" << endl;
        cout << "12. Q6 List from the digits of a number (adds 1 new list)" << endl;
        cout << "13. Q7 Merge two sorted lists (adds 1 new list)" << endl;
        cout << "14. Q8 Multiply two polynomials" << endl;
        cout << "15. Create a new list" << endl;
        cout << "16. Select a list" << endl;
        cout << "17. Show all lists" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            insert();
            display();
            break;

        case 2:
            del();
            display();
            break;

        case 3:
            search();
            break;

        case 4:
            reverse();
            display();
            break;

        case 5:
            count();
            break;

        case 6:
            display();
            break;

        case 7:
            cout << "List A (1 to " << num << "): ";
            cin >> p;
            cout << "List B (1 to " << num << "): ";
            cin >> q;

            // Check 1: both numbers must be lists that exist
            if (p < 1 || p > num || q < 1 || q > num)
            {
                cout << "Wrong list number" << endl;
                break;
            }
            // Check 2: the two lists must be different
            if (p == q)
            {
                cout << "Choose two different lists" << endl;
                break;
            }
            p--;                    // user numbers start at 1, the array at 0
            q--;

            concatenate(head[p], head[q]);
            cout << "List " << p + 1 << " (A + B): ";
            displayList(head[p]);
            cout << "List " << q + 1 << " (B, now empty): ";
            displayList(head[q]);
            break;

        case 8:
        {
            if (num + 1 > MAXS)
            {
                cout << "No room for another list" << endl;
                break;
            }
            int c = num;            // the second half goes in a new list
            if (splitList(head[cur], head[c]) == 0)
                break;              // fewer than 2 values, nothing was split
            num++;

            cout << "List " << cur + 1 << " (first half): ";
            displayList(head[cur]);
            cout << "List " << c + 1 << " (second half): ";
            displayList(head[c]);
            break;
        }

        case 9:
            cout << "Value: ";
            cin >> x;
            cout << x << " comes " << countOccur(head[cur], x) << " time(s)" << endl;
            break;

        case 10:
            display();
            maxMinTotal(head[cur]);
            break;

        case 11:
            cout << "L1 (1 to " << num << "): ";
            cin >> p;
            cout << "L2 (1 to " << num << "): ";
            cin >> q;
            cout << "L3 (1 to " << num << "): ";
            cin >> r;

            // Check 1: all three numbers must be lists that exist
            if (p < 1 || p > num || q < 1 || q > num || r < 1 || r > num)
            {
                cout << "Wrong list number" << endl;
                break;
            }
            // Check 2: the three lists must be different
            if (p == q || p == r || q == r)
            {
                cout << "Choose three different lists" << endl;
                break;
            }
            p--;
            q--;
            r--;

            evenOdd(head[p], head[q], head[r]);
            cout << "L1 (list " << p + 1 << "): ";
            displayList(head[p]);
            cout << "L2 (list " << q + 1 << ", even): ";
            displayList(head[q]);
            cout << "L3 (list " << r + 1 << ", odd): ";
            displayList(head[r]);
            break;

        case 12:
        {
            if (num + 1 > MAXS)
            {
                cout << "No room for another list" << endl;
                break;
            }
            cout << "Number: ";
            cin >> x;
            // Check 1: only numbers that are 0 or more
            if (x < 0)
            {
                cout << "Number must not be negative" << endl;
                break;
            }
            int c = num;            // the digits go in a new list
            head[c] = NULL;
            digitList(head[c], x);
            num++;

            cout << "Digits of " << x << " (list " << c + 1 << "): ";
            displayList(head[c]);
            break;
        }

        case 13:
        {
            cout << "First sorted list (1 to " << num << "): ";
            cin >> p;
            cout << "Second sorted list (1 to " << num << "): ";
            cin >> q;

            // Check 1: both numbers must be lists that exist
            if (p < 1 || p > num || q < 1 || q > num)
            {
                cout << "Wrong list number" << endl;
                break;
            }
            // Check 2: the two lists must be different
            if (p == q)
            {
                cout << "Choose two different lists" << endl;
                break;
            }
            // Check 3: room for the result list
            if (num + 1 > MAXS)
            {
                cout << "No room for another list" << endl;
                break;
            }
            p--;
            q--;

            int c = num;            // the result goes in a new list
            head[c] = NULL;
            mergeSorted(head[p], head[q], head[c]);
            num++;

            cout << "List " << p + 1 << ": ";
            displayList(head[p]);
            cout << "List " << q + 1 << ": ";
            displayList(head[q]);
            cout << "Merged (list " << c + 1 << "): ";
            displayList(head[c]);
            break;
        }

        case 14:
        {
            term *p1 = NULL, *p2 = NULL, *res = NULL;
            int t = 0, c = 0, e = 0;

            cout << "Terms in polynomial 1: ";
            cin >> t;
            for (int i = 1; i <= t; i++)
            {
                cout << "Term " << i << " (coefficient power): ";
                cin >> c >> e;
                insertTerm(p1, c, e);
            }
            cout << "Terms in polynomial 2: ";
            cin >> t;
            for (int i = 1; i <= t; i++)
            {
                cout << "Term " << i << " (coefficient power): ";
                cin >> c >> e;
                insertTerm(p2, c, e);
            }

            multiplyPoly(p1, p2, res);
            cout << "P1: ";
            displayPoly(p1);
            cout << "P2: ";
            displayPoly(p2);
            cout << "P1 * P2: ";
            displayPoly(res);
            break;
        }

        case 15:
            if (num >= MAXS)
            {
                cout << "No room for another list" << endl;
                break;
            }
            head[num] = NULL;
            cur = num;              // the new list becomes the selected one
            num++;
            cout << "List " << cur + 1 << " created and selected" << endl;
            break;

        case 16:
            cout << "List number (1 to " << num << "): ";
            cin >> k;
            if (k < 1 || k > num)
                cout << "Wrong list number" << endl;
            else
            {
                cur = k - 1;
                display();
            }
            break;

        case 17:
            for (int i = 0; i < num; i++)
            {
                cout << "List " << i + 1 << ": ";
                displayList(head[i]);
            }
            break;

        case 0:
            break;

        default:
            cout << "Wrong choice" << endl;
        }
    } while (ch != 0);
}
