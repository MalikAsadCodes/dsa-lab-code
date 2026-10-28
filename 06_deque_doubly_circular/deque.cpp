#include "deque.h"

// =====================================================
// ============== FIXED DOUBLY CIRCULAR LIST ===========
// =====================================================

// Builds maxsize nodes linked both ways.
// The last node's next is head, and head's prev is the last node.
void func::createList(node *&head)
{
    head = new node;
    head->data = 0;
    node *p = head;
    for (int i = 1; i < maxsize; i++)
    {
        node *n = new node;
        n->data = 0;
        p->next = n;        // forward link
        n->prev = p;        // backward link
        p = n;
    }
    p->next = head;         // last node -> first node
    head->prev = p;         // first node -> last node
}

// =====================================================
// ======================= DEQUE =======================
// =====================================================
// The deque lives on a doubly circular list, so values can be
// inserted and deleted at BOTH ends.
// Moving forward  (next): front on delete, rear on insert.
// Moving backward (prev): front on insert, rear on delete.

// ---------- Insert at front ----------
void func::dpushFront(node *head, node *&f, node *&r, int x)
{
    // Check 1: front and rear are both NULL (deque empty),
    // so both go to the first node
    if (f == NULL && r == NULL)
    {
        f = head;
        r = head;
        f->data = x;
        return;
    }

    // Check 2 (simple deque): front is on the first node and
    // rear is on the last node, so the deque is full
    if (f == head && r->next == head)
    {
        cout << "Deque Overflow" << endl;
        return;
    }

    // Check 3 (circular deque): front is one node after rear
    // (front = rear + 1), so the circle is full
    if (r->next == f)
    {
        cout << "Circular Deque Overflow" << endl;
        return;
    }

    // Check 4: front is on the first node, so it goes back to the last node.
    // Otherwise front simply moves one node back.
    if (f == head)
        f = head->prev;     // head's prev is the last node
    else
        f = f->prev;

    f->data = x;
}

// ---------- Insert at rear ----------
void func::dpushRear(node *head, node *&f, node *&r, int x)
{
    // Check 1: front and rear are both NULL (deque empty),
    // so both go to the first node
    if (f == NULL && r == NULL)
    {
        f = head;
        r = head;
        r->data = x;
        return;
    }

    // Check 2 (simple deque): front is on the first node and
    // rear is on the last node, so the deque is full
    if (f == head && r->next == head)
    {
        cout << "Deque Overflow" << endl;
        return;
    }

    // Check 3 (circular deque): front is one node after rear
    // (front = rear + 1), so the circle is full
    if (r->next == f)
    {
        cout << "Circular Deque Overflow" << endl;
        return;
    }

    // Check 4: rear is on the last node, so it goes back to the first node.
    // Otherwise rear simply moves one node forward.
    if (r->next == head)
        r = head;
    else
        r = r->next;

    r->data = x;
}

// ---------- Delete from front ----------
int func::dpopFront(node *head, node *&f, node *&r)
{
    // Check 1: deque is empty
    if (f == NULL)
    {
        cout << "Deque Underflow" << endl;
        return -1;
    }

    int x = f->data;

    // Check 2: only one element left, so the deque becomes empty.
    // Both pointers go to NULL and the next insert starts at the first node.
    if (f == r)
    {
        f = NULL;
        r = NULL;
        return x;
    }

    // Check 3: front is on the last node, so it goes to the first node.
    // Otherwise front simply moves one node forward.
    if (f->next == head)
        f = head;
    else
        f = f->next;
    return x;
}

// ---------- Delete from rear ----------
int func::dpopRear(node *head, node *&f, node *&r)
{
    // Check 1: deque is empty
    if (f == NULL)
    {
        cout << "Deque Underflow" << endl;
        return -1;
    }

    int x = r->data;

    // Check 2: only one element left, so the deque becomes empty.
    // Both pointers go to NULL and the next insert starts at the first node.
    if (f == r)
    {
        f = NULL;
        r = NULL;
        return x;
    }

    // Check 3: rear is on the first node, so it goes back to the last node.
    // Otherwise rear simply moves one node back.
    if (r == head)
        r = head->prev;     // head's prev is the last node
    else
        r = r->prev;
    return x;
}

// ---------- Display (front to rear, wraps through the last node) ----------
void func::ddisplay(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = f;
    node *end = r->next;    // node after rear (front itself when the deque is full)
    do                      // do...while so a full deque is still printed once
    {
        cout << p->data << " ";
        p = p->next;
    } while (p != end);
    cout << endl;
}

// ---------- Display backward (rear to front, using prev) ----------
void func::ddisplayBack(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = r;
    node *end = f->prev;    // node before front (rear itself when the deque is full)
    do
    {
        cout << p->data << " ";
        p = p->prev;
    } while (p != end);
    cout << endl;
}

// ---------- Count ----------
int func::dcount(node *f, node *r)
{
    if (f == NULL)
        return 0;
    int c = 0;
    node *p = f;
    node *end = r->next;
    do
    {
        c++;
        p = p->next;
    } while (p != end);
    return c;
}

// ---------- Search ----------
int func::dsearch(node *f, node *r, int x)
{
    if (f == NULL)
        return 0;
    node *p = f;
    node *end = r->next;
    do
    {
        if (p->data == x)
            return 1;
        p = p->next;
    } while (p != end);
    return 0;
}

// ---------- Reverse (turn the links, no data is moved) ----------
void func::dreverse(node *&f, node *&r)
{
    // Check 1: empty deque
    if (f == NULL)
    {
        cout << "Deque is empty" << endl;
        return;
    }

    // Check 2: one value, nothing to reverse
    if (f == r)
        return;

    int n = dcount(f, r);   // values in the deque
    node *a = r->next;      // first free node after the rear
    node *b = f->prev;      // last free node before the front

    // turn the next and prev link of every node from front to rear
    node *p = f;
    node *q;
    for (int i = 0; i < n; i++)
    {
        q = p->next;        // remember the old next
        p->next = p->prev;
        p->prev = q;
        p = q;
    }

    // the old rear is the new front, the old front is the new rear
    node *t = f;
    f = r;
    r = t;

    // Check 3: a == r means the deque filled the whole ring, nothing to join
    // otherwise join both ends to the free nodes again
    if (a != r)
    {
        f->prev = b;
        b->next = f;
        r->next = a;
        a->prev = r;
    }
}

// ---------- Deque Q1: split into two deques ----------
// Copy the base deque into a new ring, then cut that ring in two.
// The first half gets k = (m + 1) / 2 nodes, the second half the rest (m = nodes of the base ring).
// Returns 0 when the base ring has fewer than 2 nodes and cannot be split.
int func::splitDeque(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2)
{
    // m = nodes in the base ring (go round until we are back at head), n = values in it
    int m = 0;
    node *q = head;
    do
    {
        m++;
        q = q->next;
    } while (q != head);
    if (m < 2)
        return 0;
    int n = dcount(f, r);

    // copy the base deque into a new full-size ring
    node *c = NULL, *cf = NULL, *cr = NULL;
    createList(c);
    copyDeque(f, r, c, cf, cr);

    // last = the m-th node of the copy, the ring will end there
    node *last = c->prev;

    // mid = the k-th node, the first half ends there
    int k = (m + 1) / 2;
    node *mid = c;
    for (int i = 1; i < k; i++)
        mid = mid->next;

    h1 = c;
    h2 = mid->next;
    mid->next = c;          // first ring: last node -> first node
    c->prev = mid;          //             first node -> last node
    last->next = h2;        // second ring: last node -> first node
    h2->prev = last;        //              first node -> last node

    // front and rear: all values fit in the first half, or they spill into the second
    f1 = cf;
    if (n <= k)
    {
        r1 = cr;
        f2 = NULL;
        r2 = NULL;
    }
    else
    {
        r1 = mid;
        f2 = h2;
        r2 = cr;
    }
    return 1;
}

// ---------- Deque Q2: even values go to (eh, evF, evR), odd to (oh, odF, odR) ----------
void func::devenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR)
{
    evF = NULL;
    evR = NULL;
    odF = NULL;
    odR = NULL;
    if (f == NULL)
        return;
    node *p = f;
    node *end = r->next;
    do
    {
        if (p->data % 2 == 0)
            dpushRear(eh, evF, evR, p->data);
        else
            dpushRear(oh, odF, odR, p->data);
        p = p->next;
    } while (p != end);
}

// ---------- Deque Q3: next greater element (wraps from rear back to front) ----------
void func::dnextGreater(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "Deque is empty" << endl;
        return;
    }
    int n = dcount(f, r);
    node *p = f;
    for (int i = 0; i < n; i++)
    {
        int nge = -1;
        node *q = p;
        // look at the other n - 1 elements after p
        for (int k = 1; k < n; k++)
        {
            if (q == r)
                q = f;              // rear reached, wrap to front
            else
                q = q->next;

            if (q->data > p->data)
            {
                nge = q->data;
                break;
            }
        }
        cout << p->data << " -> " << nge << endl;
        p = p->next;
    }
}

// ---------- Deque Q5: bubble sort ----------
void func::dsortList(node *f, node *r)
{
    int n = dcount(f, r);
    for (int i = 0; i < n - 1; i++)
    {
        node *p = f;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p->data > p->next->data)
            {
                int t = p->data;
                p->data = p->next->data;
                p->next->data = t;
            }
            p = p->next;
        }
    }
}

// ---------- Deque Q6: palindrome (uses the temporary deque) ----------
// Insert every character at the rear, then take one from each end and compare:
// first with last, second with second-last, and so on.
int func::disPalindrome(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
        dpushRear(dtmp, tf, tr, s[i]);

    int same = 0;
    for (int i = 0; i < len / 2; i++)
    {
        int a = dpopFront(dtmp, tf, tr);
        int b = dpopRear(dtmp, tf, tr);
        if (a == b)
            same++;
    }
    if (same == len / 2)
        return 1;
    return 0;
}

// ---------- Deque Q7: copy (f, r) into (ch, cf, cr) ----------
void func::copyDeque(node *f, node *r, node *ch, node *&cf, node *&cr)
{
    cf = NULL;
    cr = NULL;
    if (f == NULL)
        return;
    node *p = f;
    node *end = r->next;
    do
    {
        dpushRear(ch, cf, cr, p->data);
        p = p->next;
    } while (p != end);
}

// ---------- Deque Q8: balanced brackets (uses the temporary deque) ----------
// Opening brackets go in at the rear, a closing bracket takes the newest one from the rear.
int func::disBalanced(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        char ch = s[i];
        // opening bracket: insert it at the rear
        if (ch == '(' || ch == '{' || ch == '[')
            dpushRear(dtmp, tf, tr, ch);
        // closing bracket: it must match the last opening bracket
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (tf == NULL)                 // nothing to match with
                return 0;
            char open = dpopRear(dtmp, tf, tr);
            if (ch == ')' && open == '(')
                continue;
            if (ch == '}' && open == '{')
                continue;
            if (ch == ']' && open == '[')
                continue;
            return 0;                       // wrong pair
        }
    }
    // balanced only if no opening bracket is left
    if (tf == NULL)
        return 1;
    return 0;
}

// ---------- Deque Q9: remove duplicates (uses the temporary deque) ----------
void func::dremoveDuplicates(node *head, node *&f, node *&r)
{
    node *tf = NULL, *tr = NULL;
    // take values from the front, keep only the first time each value is seen
    while (f != NULL)
    {
        int x = dpopFront(head, f, r);
        if (dsearch(tf, tr, x) == 0)
            dpushRear(dtmp, tf, tr, x);
    }
    // move them back in the same order
    while (tf != NULL)
    {
        int x = dpopFront(dtmp, tf, tr);
        dpushRear(head, f, r, x);
    }
}

// ---------- Deque Q10: values found in both (f1, r1) and (f2, r2), result in (rh, rf, rr) ----------
void func::dintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr)
{
    rf = NULL;
    rr = NULL;

    // either deque empty, so nothing is common
    if (f1 == NULL || f2 == NULL)
        return;

    // walk the first deque, counted (a ring has no NULL end)
    int n = dcount(f1, r1);
    node *p = f1;
    for (int i = 0; i < n; i++)
    {
        // insert if it is in the second one and not already in the result
        if (dsearch(f2, r2, p->data) == 1 && dsearch(rf, rr, p->data) == 0)
            dpushRear(rh, rf, rr, p->data);
        p = p->next;
    }
}

// =====================================================
// ====================== MENUS ========================
// =====================================================

void func::dequeMenu()
{
    int ch = 0, x = 0, n = 0;
    string s;
    do
    {
        // h, f and r are the head, front and rear of the selected deque
        node *&h = dhead[dcur];
        node *&f = dfront[dcur];
        node *&r = drear[dcur];

        cout << "\n--- DEQUE " << dcur + 1 << " (of " << dnum << ") ---" << endl;
        cout << "1. Insert at front" << endl;
        cout << "2. Insert at rear" << endl;
        cout << "3. Delete from front" << endl;
        cout << "4. Delete from rear" << endl;
        cout << "5. Display (front to rear)" << endl;
        cout << "6. Display backward (rear to front)" << endl;
        cout << "7. Count" << endl;
        cout << "8. Search" << endl;
        cout << "9. Reverse" << endl;
        cout << "10. Q1 Split into two deques (adds 2 new deques)" << endl;
        cout << "11. Q2 Even / Odd deques (adds 2 new deques)" << endl;
        cout << "12. Q3 Next greater element (wraps around)" << endl;
        cout << "13. Q5 Sort (bubble sort)" << endl;
        cout << "14. Q6 Palindrome check" << endl;
        cout << "15. Q7 Copy the deque (adds 1 new deque)" << endl;
        cout << "16. Q8 Balanced brackets" << endl;
        cout << "17. Q9 Remove duplicates" << endl;
        cout << "18. Q10 Intersection of two deques (adds 1 new deque)" << endl;
        cout << "19. Create a new deque" << endl;
        cout << "20. Select a deque" << endl;
        cout << "21. Show all deques" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Value: ";
            cin >> x;
            dpushFront(h, f, r, x);
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            break;

        case 2:
            cout << "Value: ";
            cin >> x;
            dpushRear(h, f, r, x);
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            break;

        case 3:
            if (f == NULL)
                cout << "Deque Underflow" << endl;
            else
                cout << "Deleted from front: " << dpopFront(h, f, r) << endl;
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            break;

        case 4:
            if (f == NULL)
                cout << "Deque Underflow" << endl;
            else
                cout << "Deleted from rear: " << dpopRear(h, f, r) << endl;
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            break;

        case 5:
            cout << "Deque " << dcur + 1 << " (front first): ";
            ddisplay(f, r);
            break;

        case 6:
            cout << "Deque " << dcur + 1 << " (rear first): ";
            ddisplayBack(f, r);
            break;

        case 7:
            cout << "Count: " << dcount(f, r) << endl;
            break;

        case 8:
            cout << "Value to search: ";
            cin >> x;
            if (dsearch(f, r, x) == 1)
                cout << x << " found" << endl;
            else
                cout << x << " not found" << endl;
            break;

        case 9:
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            dreverse(f, r);         // f and r are references, so the new front and rear are kept
            cout << "Reversed deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            break;

        case 10:
        {
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            if (dnum + 2 > MAXS)
            {
                cout << "No room for two more deques" << endl;
                break;
            }
            // two new deques at the end of the array: a is the first half, b the second
            int a = dnum, b = dnum + 1;
            if (splitDeque(h, f, r, dhead[a], dfront[a], drear[a], dhead[b], dfront[b], drear[b]) == 0)
            {
                cout << "Deque has fewer than 2 nodes, it cannot be split" << endl;
                break;
            }
            dnum += 2;

            cout << "Whole deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            cout << "Deque " << a + 1 << " (first half): ";
            ddisplay(dfront[a], drear[a]);
            cout << "Deque " << b + 1 << " (second half): ";
            ddisplay(dfront[b], drear[b]);
            break;
        }

        case 11:
        {
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            if (dnum + 2 > MAXS)
            {
                cout << "No room for two more deques" << endl;
                break;
            }
            // two new deques at the end of the array: e for even, o for odd
            int e = dnum, o = dnum + 1;
            createList(dhead[e]);
            dfront[e] = NULL;
            drear[e] = NULL;
            createList(dhead[o]);
            dfront[o] = NULL;
            drear[o] = NULL;
            dnum += 2;

            devenOdd(f, r, dhead[e], dfront[e], drear[e], dhead[o], dfront[o], drear[o]);
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            cout << "Even deque (deque " << e + 1 << "): ";
            ddisplay(dfront[e], drear[e]);
            cout << "Odd deque (deque " << o + 1 << "): ";
            ddisplay(dfront[o], drear[o]);
            cout << "Use 'Select a deque' to work on deque " << e + 1 << " or " << o + 1 << endl;
            break;
        }

        case 12:
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            cout << "Deque " << dcur + 1 << ": ";
            ddisplay(f, r);
            dnextGreater(f, r);
            break;

        case 13:
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            ddisplay(f, r);
            dsortList(f, r);
            cout << "After: ";
            ddisplay(f, r);
            break;

        case 14:
            cout << "Enter string: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Deque Overflow: string is longer than " << maxsize << " characters" << endl;
            else if (disPalindrome(s) == 1)
                cout << "Palindrome" << endl;
            else
                cout << "Not Palindrome" << endl;
            break;

        case 15:
        {
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            if (dnum + 1 > MAXS)
            {
                cout << "No room for another deque" << endl;
                break;
            }
            int c = dnum;               // the copy goes in a new deque
            createList(dhead[c]);
            dfront[c] = NULL;
            drear[c] = NULL;
            dnum++;

            copyDeque(f, r, dhead[c], dfront[c], drear[c]);
            cout << "Original (deque " << dcur + 1 << "): ";
            ddisplay(f, r);
            cout << "Copy (deque " << c + 1 << "): ";
            ddisplay(dfront[c], drear[c]);
            break;
        }

        case 16:
            cout << "Enter brackets: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Deque Overflow: more than " << maxsize << " brackets" << endl;
            else if (disBalanced(s) == 1)
                cout << "true (Balanced)" << endl;
            else
                cout << "false (Not Balanced)" << endl;
            break;

        case 17:
            if (f == NULL)
            {
                cout << "Deque is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            ddisplay(f, r);
            dremoveDuplicates(h, f, r);
            cout << "After: ";
            ddisplay(f, r);
            break;

        case 18:
        {
            int a = 0, b = 0;
            cout << "First deque (1 to " << dnum << "): ";
            cin >> a;
            cout << "Second deque (1 to " << dnum << "): ";
            cin >> b;

            // Check 1: both numbers must be deques that exist
            if (a < 1 || a > dnum || b < 1 || b > dnum)
            {
                cout << "Wrong deque number" << endl;
                break;
            }
            // Check 2: the two deques must be different
            if (a == b)
            {
                cout << "Choose two different deques" << endl;
                break;
            }
            a--;                        // user numbers start at 1, the array at 0
            b--;
            // Check 3: neither deque may be empty
            if (dfront[a] == NULL)
            {
                cout << "Deque " << a + 1 << " is empty, insert some values first" << endl;
                break;
            }
            if (dfront[b] == NULL)
            {
                cout << "Deque " << b + 1 << " is empty, insert some values first" << endl;
                break;
            }
            // Check 4: room for the result deque
            if (dnum + 1 > MAXS)
            {
                cout << "No room for another deque" << endl;
                break;
            }

            int res = dnum;             // the result goes in a new deque
            createList(dhead[res]);
            dfront[res] = NULL;
            drear[res] = NULL;
            dnum++;

            dintersection(dfront[a], drear[a], dfront[b], drear[b], dhead[res], dfront[res], drear[res]);
            cout << "Deque " << a + 1 << ": ";
            ddisplay(dfront[a], drear[a]);
            cout << "Deque " << b + 1 << ": ";
            ddisplay(dfront[b], drear[b]);
            cout << "Intersection (deque " << res + 1 << "): ";
            ddisplay(dfront[res], drear[res]);
            break;
        }

        case 19:
            if (dnum >= MAXS)
            {
                cout << "No room for another deque" << endl;
                break;
            }
            createList(dhead[dnum]);
            dfront[dnum] = NULL;
            drear[dnum] = NULL;
            dcur = dnum;                // the new deque becomes the selected one
            dnum++;
            cout << "Deque " << dcur + 1 << " created and selected" << endl;
            break;

        case 20:
            cout << "Deque number (1 to " << dnum << "): ";
            cin >> n;
            if (n < 1 || n > dnum)
                cout << "Wrong deque number" << endl;
            else
            {
                dcur = n - 1;
                cout << "Deque " << n << " selected: ";
                ddisplay(dfront[dcur], drear[dcur]);
            }
            break;

        case 21:
            for (int i = 0; i < dnum; i++)
            {
                cout << "Deque " << i + 1 << ": ";
                ddisplay(dfront[i], drear[i]);
            }
            break;

        case 0:
            break;

        default:
            cout << "Wrong choice" << endl;
        }
    } while (ch > 0);
}

void func::menu()
{
    // start with one deque, plus the temporary deque
    createList(dhead[0]);       // a doubly circular list of maxsize nodes
    dnum = 1;
    createList(dtmp);

    dequeMenu();
}
