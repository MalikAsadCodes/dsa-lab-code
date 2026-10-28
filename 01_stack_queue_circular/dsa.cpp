#include "dsa.h"

// =====================================================
// =================== FIXED LIST ======================
// =====================================================

// Builds maxsize nodes. If circular == 1 the last node points back to head.
void func::createList(node *&head, int circular)
{
    head = new node;
    head->data = 0;
    node *p = head;
    for (int i = 1; i < maxsize; i++)
    {
        node *n = new node;
        n->data = 0;
        p->next = n;
        p = n;
    }
    p->next = NULL;
    if (circular == 1)
        p->next = head;
}

// Returns the node before p, starting the search from start
node *func::prevNode(node *start, node *p)
{
    if (p == start)
        return NULL;
    node *q = start;
    while (q->next != p)
        q = q->next;
    return q;
}

// =====================================================
// ===================== STACK =========================
// =====================================================

void func::push(node *head, node *&top, int x)
{
    if (top == NULL)
    {
        top = head;
        top->data = x;
        return;
    }
    if (top->next == NULL)
    {
        cout << "Stack Overflow" << endl;
        return;
    }
    top = top->next;
    top->data = x;
}

int func::pop(node *head, node *&top)
{
    if (top == NULL)
    {
        cout << "Stack Underflow" << endl;
        return -1;
    }
    int x = top->data;
    top = prevNode(head, top);
    return x;
}

void func::display(node *head, node *top)
{
    if (top == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = top;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = prevNode(head, p);
    }
    cout << endl;
}

int func::search(node *head, node *top, int x)
{
    if (top == NULL)
        return 0;
    node *p = head;
    node *end = top->next;
    while (p != end)
    {
        if (p->data == x)
            return 1;
        p = p->next;
    }
    return 0;
}

// ---------- Stack Q1: split into two stacks ----------
// Q1 as real stacks: copy the base stack into a new list, then cut that list in two.
// The first half gets k = (m + 1) / 2 nodes, the second half the rest (m = nodes of the base stack).
// Returns 0 when the base stack has fewer than 2 nodes and cannot be split.
int func::splitStack(node *head, node *top, node *&h1, node *&t1, node *&h2, node *&t2)
{
    // m = nodes in the base stack, n = values in it
    int m = 0;
    for (node *p = head; p != NULL; p = p->next)
        m++;
    if (m < 2)
        return 0;
    int n = 0;
    if (top != NULL)
        for (node *p = head; p != top->next; p = p->next)
            n++;

    // copy the base stack into a new full-size list
    node *c = NULL, *ct = NULL;
    createList(c, 0);
    copyStack(head, top, c, ct);

    // keep only m nodes, so the copy has the same size as the base stack
    node *last = c;
    for (int i = 1; i < m; i++)
        last = last->next;
    last->next = NULL;

    // cut after the k-th node: the first half ends there, the second half starts after it
    int k = (m + 1) / 2;
    node *mid = c;
    for (int i = 1; i < k; i++)
        mid = mid->next;
    h1 = c;
    h2 = mid->next;
    mid->next = NULL;

    // tops: all values fit in the first half, or they spill into the second
    if (n <= k)
    {
        t1 = ct;
        t2 = NULL;
    }
    else
    {
        t1 = mid;
        t2 = ct;

        // the top of stack 2 must be on its first value (the one next to the cut),
        // so reverse the values of the second half: the last value goes to the bottom
        int cnt = n - k;                        // values in the second half
        for (int i = 0; i < cnt / 2; i++)
        {
            node *a = h2, *b = h2;
            for (int j = 0; j < i; j++)
                a = a->next;                    // i-th node from the bottom
            for (int j = 0; j < cnt - 1 - i; j++)
                b = b->next;                    // i-th node from the top
            int tmp = a->data;
            a->data = b->data;
            b->data = tmp;
        }
    }
    return 1;
}

// ---------- Stack Q2: even values go to (eh, et), odd values to (oh, ot) ----------

void func::evenOdd(node *head, node *top, node *eh, node *&et, node *oh, node *&ot)
{
    et = NULL;
    ot = NULL;
    if (top == NULL)
        return;
    node *p = head;
    node *end = top->next;
    while (p != end)
    {
        if (p->data % 2 == 0)
            push(eh, et, p->data);
        else
            push(oh, ot, p->data);
        p = p->next;
    }
}

// ---------- Stack Q3: next greater element ----------

void func::nextGreater(node *head, node *top)
{
    if (top == NULL)
    {
        cout << "Stack is empty" << endl;
        return;
    }
    node *p = top;
    while (p != NULL)
    {
        int nge = -1;
        node *q = prevNode(head, p);
        while (q != NULL)
        {
            if (q->data > p->data)
            {
                nge = q->data;
                break;
            }
            q = prevNode(head, q);
        }
        cout << p->data << " -> " << nge << endl;
        p = prevNode(head, p);
    }
}

// ---------- Stack Q5: bubble sort ----------

void func::sortList(node *head, node *top)
{
    if (top == NULL)
        return;
    int n = 0;
    node *p = head;
    node *end = top->next;
    while (p != end)
    {
        n++;
        p = p->next;
    }
    for (int i = 0; i < n - 1; i++)
    {
        p = head;
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p->data < p->next->data)
            {
                int t = p->data;
                p->data = p->next->data;
                p->next->data = t;
            }
            p = p->next;
        }
    }
}

// ---------- Stack Q6: palindrome (uses the temporary stack) ----------

int func::isPalindrome(string s)
{
    node *t = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
        push(stmp, t, s[i]);

    int same = 0;
    for (int i = 0; i < len; i++)
    {
        if (pop(stmp, t) == s[i])
            same++;
    }
    if (same == len)
        return 1;
    return 0;
}

// ---------- Stack Q7: copy (head, top) into (ch, ct) ----------

void func::copyStack(node *head, node *top, node *ch, node *&ct)
{
    ct = NULL;
    if (top == NULL)
        return;
    node *p = head;
    node *end = top->next;
    while (p != end)
    {
        push(ch, ct, p->data);
        p = p->next;
    }
}

// ---------- Stack Q8: balanced brackets (uses the temporary stack) ----------

int func::isBalanced(string s)
{
    node *t = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        char ch = s[i];
        if (ch == '(' || ch == '{' || ch == '[')
            push(stmp, t, ch);
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (t == NULL)
                return 0;
            char open = pop(stmp, t);
            if (ch == ')' && open == '(')
                continue;
            if (ch == '}' && open == '{')
                continue;
            if (ch == ']' && open == '[')
                continue;
            return 0;
        }
    }
    if (t == NULL)
        return 1;
    return 0;
}

// ---------- Stack Q9: remove duplicates (uses the temporary stack) ----------

void func::removeDuplicates(node *head, node *&top)
{
    node *t = NULL;
    // move unique values into the temporary stack
    while (top != NULL)
    {
        int x = pop(head, top);
        if (search(stmp, t, x) == 0)
            push(stmp, t, x);
    }
    // move them back
    while (t != NULL)
        push(head, top, pop(stmp, t));
}

// ---------- Stack Q10: values found in both (h1, t1) and (h2, t2), result in (rh, rt) ----------

void func::intersection(node *h1, node *t1, node *h2, node *t2, node *rh, node *&rt)
{
    rt = NULL;
    // either stack empty, so nothing is common
    if (t1 == NULL || t2 == NULL)
        return;
    // walk the first stack from bottom to top
    node *p = h1;
    node *end = t1->next;
    while (p != end)
    {
        // push if it is in the second stack and not already in the result
        if (search(h2, t2, p->data) == 1 && search(rh, rt, p->data) == 0)
            push(rh, rt, p->data);
        p = p->next;
    }
}

// =====================================================
// ===================== QUEUE =========================
// =====================================================

void func::qpush(node *head, node *&f, node *&r, int x)
{
    if (r == NULL)
    {
        f = head;
        r = head;
        r->data = x;
        return;
    }
    if (r->next == NULL)
    {
        cout << "Queue Overflow" << endl;
        return;
    }
    r = r->next;
    r->data = x;
}

int func::qpop(node *&head, node *&f, node *&r)
{
    if (f == NULL)
    {
        cout << "Queue Underflow" << endl;
        return -1;
    }
    int x = f->data;
    if (f == r)
    {
        f = NULL;
        r = NULL;
        return x;
    }
    node *e = f;
    f = f->next;
    head = f;
    e->next = r->next;
    r->next = e;
    return x;
}

void func::qdisplay(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = f;
    node *end = r->next;
    while (p != end)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int func::qcount(node *f, node *r)
{
    if (f == NULL)
        return 0;
    int c = 0;
    node *p = f;
    node *end = r->next;
    while (p != end)
    {
        c++;
        p = p->next;
    }
    return c;
}

int func::qsearch(node *f, node *r, int x)
{
    if (f == NULL)
        return 0;
    node *p = f;
    node *end = r->next;
    while (p != end)
    {
        if (p->data == x)
            return 1;
        p = p->next;
    }
    return 0;
}

void func::qreverse(node *f, node *r)
{
    int n = qcount(f, r);
    node *a = f;
    node *b = r;
    for (int i = 0; i < n / 2; i++)
    {
        int t = a->data;
        a->data = b->data;
        b->data = t;
        a = a->next;
        b = prevNode(f, b);
    }
}

int func::qpopLast(node *&f, node *&r)
{
    if (f == NULL)
    {
        cout << "Queue Underflow" << endl;
        return -1;
    }
    int x = r->data;
    if (f == r)
    {
        f = NULL;
        r = NULL;
    }
    else
        r = prevNode(f, r);
    return x;
}

// ---------- Queue Q1: split into two queues ----------
// Q1 as real queues: copy the base queue into a new list, then cut that list in two.
// The first half gets k = (m + 1) / 2 nodes, the second half the rest (m = nodes of the base queue).
// Returns 0 when the base queue has fewer than 2 nodes and cannot be split.
int func::splitQueue(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2)
{
    // m = nodes in the base queue, n = values in it
    int m = 0;
    for (node *p = head; p != NULL; p = p->next)
        m++;
    if (m < 2)
        return 0;
    int n = qcount(f, r);

    // copy the base queue into a new full-size list
    node *c = NULL, *cf = NULL, *cr = NULL;
    createList(c, 0);
    copyQueue(f, r, c, cf, cr);

    // keep only m nodes, so the copy has the same size as the base queue
    node *last = c;
    for (int i = 1; i < m; i++)
        last = last->next;
    last->next = NULL;

    // cut after the k-th node: the first half ends there, the second half starts after it
    int k = (m + 1) / 2;
    node *mid = c;
    for (int i = 1; i < k; i++)
        mid = mid->next;
    h1 = c;
    h2 = mid->next;
    mid->next = NULL;

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

// ---------- Queue Q2: even values go to (eh, evF, evR), odd to (oh, odF, odR) ----------

void func::qevenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR)
{
    evF = NULL;
    evR = NULL;
    odF = NULL;
    odR = NULL;
    if (f == NULL)
        return;
    node *p = f;
    node *end = r->next;
    while (p != end)
    {
        if (p->data % 2 == 0)
            qpush(eh, evF, evR, p->data);
        else
            qpush(oh, odF, odR, p->data);
        p = p->next;
    }
}

// ---------- Queue Q3: next greater element ----------

void func::qnextGreater(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }
    node *end = r->next;
    node *p = f;
    while (p != end)
    {
        int nge = -1;
        node *q = p->next;
        while (q != end)
        {
            if (q->data > p->data)
            {
                nge = q->data;
                break;
            }
            q = q->next;
        }
        cout << p->data << " -> " << nge << endl;
        p = p->next;
    }
}

// ---------- Queue Q5: bubble sort ----------

void func::qsortList(node *f, node *r)
{
    int n = qcount(f, r);
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

// ---------- Queue Q6: palindrome (uses the temporary queue) ----------

int func::qisPalindrome(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
        qpush(qtmp, tf, tr, s[i]);

    int same = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (qpop(qtmp, tf, tr) == s[i])
            same++;
    }
    if (same == len)
        return 1;
    return 0;
}

// ---------- Queue Q7: copy (f, r) into (ch, cf, cr) ----------

void func::copyQueue(node *f, node *r, node *ch, node *&cf, node *&cr)
{
    cf = NULL;
    cr = NULL;
    if (f == NULL)
        return;
    node *p = f;
    node *end = r->next;
    while (p != end)
    {
        qpush(ch, cf, cr, p->data);
        p = p->next;
    }
}

// ---------- Queue Q8: balanced brackets (uses the temporary queue) ----------

int func::qisBalanced(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        char ch = s[i];
        if (ch == '(' || ch == '{' || ch == '[')
            qpush(qtmp, tf, tr, ch);
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (tf == NULL)
                return 0;
            char open = qpopLast(tf, tr);
            if (ch == ')' && open == '(')
                continue;
            if (ch == '}' && open == '{')
                continue;
            if (ch == ']' && open == '[')
                continue;
            return 0;
        }
    }
    if (tf == NULL)
        return 1;
    return 0;
}

// ---------- Queue Q9: remove duplicates (uses the temporary queue) ----------

void func::qremoveDuplicates(node *&head, node *&f, node *&r)
{
    node *tf = NULL, *tr = NULL;
    // move unique values into the temporary queue
    while (f != NULL)
    {
        int x = qpop(head, f, r);
        if (qsearch(tf, tr, x) == 0)
            qpush(qtmp, tf, tr, x);
    }
    // move them back
    while (tf != NULL)
    {
        int x = qpop(qtmp, tf, tr);
        qpush(head, f, r, x);
    }
}

// ---------- Queue Q10: values found in both (f1, r1) and (f2, r2), result in (rh, rf, rr) ----------

void func::qintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr)
{
    rf = NULL;
    rr = NULL;
    // either queue empty, so nothing is common
    if (f1 == NULL || f2 == NULL)
        return;
    // walk the first queue from front to rear
    node *p = f1;
    node *end = r1->next;
    while (p != end)
    {
        // insert if it is in the second queue and not already in the result
        if (qsearch(f2, r2, p->data) == 1 && qsearch(rf, rr, p->data) == 0)
            qpush(rh, rf, rr, p->data);
        p = p->next;
    }
}

// =====================================================
// ================= CIRCULAR QUEUE ====================
// =====================================================

// ---------- Insert ----------
void func::cpush(node *head, node *&f, node *&r, int x)
{
    // Check 1: front and rear are both NULL (queue empty),
    // so both go to the first node
    if (f == NULL && r == NULL)
    {
        f = head;
        r = head;
        r->data = x;
        return;
    }

    // Check 2 (simple queue): front is on the first node and
    // rear is on the last node, so the queue is full
    if (f == head && r->next == head)
    {
        cout << "Queue Overflow" << endl;
        return;
    }

    // Check 3 (circular queue): front is one node after rear
    // (front = rear + 1), so the circle is full
    if (r->next == f)
    {
        cout << "Circular Queue Overflow" << endl;
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

// ---------- Delete ----------
int func::cpop(node *&f, node *&r)
{
    // Check 1: queue is empty
    if (f == NULL)
    {
        cout << "Circular Queue Underflow" << endl;
        return -1;
    }

    int x = f->data;

    // Check 2: only one element left, so the queue becomes empty.
    // Both pointers go to NULL and the next insert starts at the first node.
    if (f == r)
    {
        f = NULL;
        r = NULL;
        return x;
    }

    // Move front forward. If front is on the last node,
    // its next is the first node, so front wraps to the first node.
    f = f->next;
    return x;
}

// ---------- Display (front to rear, wraps through the last node) ----------
void func::cdisplay(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "empty" << endl;
        return;
    }
    node *p = f;
    node *end = r->next;    // node after rear (front itself when the circle is full)
    do                      // do...while so a full circle is still printed once
    {
        cout << p->data << " ";
        p = p->next;
    } while (p != end);
    cout << endl;
}

// ---------- Count ----------
int func::ccount(node *f, node *r)
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
int func::csearch(node *f, node *r, int x)
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

// ---------- Reverse (swap values from both ends) ----------
void func::creverse(node *f, node *r)
{
    int n = ccount(f, r);
    node *a = f;            // walks forward from front
    node *b = r;            // walks backward from rear
    for (int i = 0; i < n / 2; i++)
    {
        int t = a->data;
        a->data = b->data;
        b->data = t;
        a = a->next;
        b = prevNode(f, b);
    }
}

// ---------- Remove from the rear (used by the bracket check) ----------
int func::cpopLast(node *&f, node *&r)
{
    // Check 1: queue is empty
    if (f == NULL)
    {
        cout << "Circular Queue Underflow" << endl;
        return -1;
    }
    int x = r->data;

    // Check 2: only one element, so the queue becomes empty
    if (f == r)
    {
        f = NULL;
        r = NULL;
    }
    // Otherwise rear moves one node back
    else
        r = prevNode(f, r);
    return x;
}

// ---------- Circular Queue Q1: split into two circular queues ----------
// Q1 as real circular queues: copy the base queue into a new ring, then cut that ring in two.
// The first half gets k = (m + 1) / 2 nodes, the second half the rest (m = nodes of the base ring).
// Returns 0 when the base ring has fewer than 2 nodes and cannot be split.
int func::splitCircular(node *head, node *f, node *r, node *&h1, node *&f1, node *&r1, node *&h2, node *&f2, node *&r2)
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
    int n = ccount(f, r);

    // copy the base queue into a new full-size ring
    node *c = NULL, *cf = NULL, *cr = NULL;
    createList(c, 1);
    copyCircular(f, r, c, cf, cr);

    // last = the m-th node of the copy, the ring will end there
    node *last = c;
    for (int i = 1; i < m; i++)
        last = last->next;

    // mid = the k-th node, the first half ends there
    int k = (m + 1) / 2;
    node *mid = c;
    for (int i = 1; i < k; i++)
        mid = mid->next;

    h1 = c;
    h2 = mid->next;
    mid->next = c;          // first ring: its last node points back to its first node
    last->next = h2;        // second ring: its last node points back to its first node

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

// ---------- Q2: even values go to (eh, evF, evR), odd to (oh, odF, odR) ----------
void func::cevenOdd(node *f, node *r, node *eh, node *&evF, node *&evR, node *oh, node *&odF, node *&odR)
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
            cpush(eh, evF, evR, p->data);
        else
            cpush(oh, odF, odR, p->data);
        p = p->next;
    } while (p != end);
}

// ---------- Q3: next greater element (wraps from rear back to front) ----------
void func::cnextGreater(node *f, node *r)
{
    if (f == NULL)
    {
        cout << "Circular Queue is empty" << endl;
        return;
    }
    int n = ccount(f, r);
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

// ---------- Q5: bubble sort ----------
void func::csortList(node *f, node *r)
{
    int n = ccount(f, r);
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

// ---------- Q6: palindrome (uses the temporary circular queue) ----------
int func::cisPalindrome(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
        cpush(ctmp, tf, tr, s[i]);

    // delete from the front and compare with the string from the back
    int same = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (cpop(tf, tr) == s[i])
            same++;
    }
    if (same == len)
        return 1;
    return 0;
}

// ---------- Q7: copy (f, r) into (ch, cf, cr) ----------
void func::copyCircular(node *f, node *r, node *ch, node *&cf, node *&cr)
{
    cf = NULL;
    cr = NULL;
    if (f == NULL)
        return;
    node *p = f;
    node *end = r->next;
    do
    {
        cpush(ch, cf, cr, p->data);
        p = p->next;
    } while (p != end);
}

// ---------- Q8: balanced brackets (uses the temporary circular queue) ----------
int func::cisBalanced(string s)
{
    node *tf = NULL, *tr = NULL;
    int len = s.length();
    for (int i = 0; i < len; i++)
    {
        char ch = s[i];
        // opening bracket: insert it
        if (ch == '(' || ch == '{' || ch == '[')
            cpush(ctmp, tf, tr, ch);
        // closing bracket: it must match the last opening bracket
        else if (ch == ')' || ch == '}' || ch == ']')
        {
            if (tf == NULL)                 // nothing to match with
                return 0;
            char open = cpopLast(tf, tr);
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

// ---------- Q9: remove duplicates (uses the temporary circular queue) ----------
void func::cremoveDuplicates(node *head, node *&f, node *&r)
{
    node *tf = NULL, *tr = NULL;
    // move unique values into the temporary circular queue
    while (f != NULL)
    {
        int x = cpop(f, r);
        if (csearch(tf, tr, x) == 0)
            cpush(ctmp, tf, tr, x);
    }
    // move them back
    while (tf != NULL)
    {
        int x = cpop(tf, tr);
        cpush(head, f, r, x);
    }
}

// ---------- Q10: values found in both (f1, r1) and (f2, r2), result in (rh, rf, rr) ----------
void func::cintersection(node *f1, node *r1, node *f2, node *r2, node *rh, node *&rf, node *&rr)
{
    rf = NULL;
    rr = NULL;

    // either circular queue empty, so nothing is common
    if (f1 == NULL || f2 == NULL)
        return;

    // walk the first circular queue, counted (a ring has no NULL end)
    int n = ccount(f1, r1);
    node *p = f1;
    for (int i = 0; i < n; i++)
    {
        // insert if it is in the second one and not already in the result
        if (csearch(f2, r2, p->data) == 1 && csearch(rf, rr, p->data) == 0)
            cpush(rh, rf, rr, p->data);
        p = p->next;
    }
}

// =====================================================
// ====================== MENUS ========================
// =====================================================

void func::stackMenu()
{
    int ch = 0, x = 0, n = 0;
    string s;
    do
    {
        // h and t are the head and top of the selected stack
        node *&h = shead[scur];
        node *&t = stop[scur];

        cout << "\n--- STACK " << scur + 1 << " (of " << snum << ") ---" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Display" << endl;
        cout << "4. Q1  Split into two stacks (adds 2 new stacks)" << endl;
        cout << "5. Q2  Even / Odd stacks (adds 2 new stacks)" << endl;
        cout << "6. Q3  Next greater element" << endl;
        cout << "7. Q5  Sort (bubble sort)" << endl;
        cout << "8. Q6  Palindrome check" << endl;
        cout << "9. Q7  Copy the stack (adds 1 new stack)" << endl;
        cout << "10. Q8 Balanced brackets" << endl;
        cout << "11. Q9 Remove duplicates" << endl;
        cout << "12. Q10 Intersection of two stacks (adds 1 new stack)" << endl;
        cout << "13. Create a new stack" << endl;
        cout << "14. Select a stack" << endl;
        cout << "15. Show all stacks" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Value: ";
            cin >> x;
            push(h, t, x);
            cout << "Stack " << scur + 1 << ": ";
            display(h, t);
            break;

        case 2:
            if (t == NULL)
                cout << "Stack Underflow" << endl;
            else
                cout << "Popped: " << pop(h, t) << endl;
            cout << "Stack " << scur + 1 << ": ";
            display(h, t);
            break;

        case 3:
            cout << "Stack " << scur + 1 << " (top first): ";
            display(h, t);
            break;

        case 4:
        {
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            if (snum + 2 > MAXS)
            {
                cout << "No room for two more stacks" << endl;
                break;
            }
            // two new stacks at the end of the array: a is the first half, b the second
            int a = snum, b = snum + 1;
            if (splitStack(h, t, shead[a], stop[a], shead[b], stop[b]) == 0)
            {
                cout << "Stack has fewer than 2 nodes, it cannot be split" << endl;
                break;
            }
            snum += 2;

            cout << "Whole stack " << scur + 1 << ": ";
            display(h, t);
            cout << "Stack " << a + 1 << " (first half): ";
            display(shead[a], stop[a]);
            cout << "Stack " << b + 1 << " (second half): ";
            display(shead[b], stop[b]);
            break;
        }

        case 5:
        {
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            if (snum + 2 > MAXS)
            {
                cout << "No room for two more stacks" << endl;
                break;
            }
            // two new stacks at the end of the array: e for even, o for odd
            int e = snum, o = snum + 1;
            createList(shead[e], 0);
            stop[e] = NULL;
            createList(shead[o], 0);
            stop[o] = NULL;
            snum += 2;

            evenOdd(h, t, shead[e], stop[e], shead[o], stop[o]);
            cout << "Stack " << scur + 1 << ": ";
            display(h, t);
            cout << "Even stack (stack " << e + 1 << "): ";
            display(shead[e], stop[e]);
            cout << "Odd stack (stack " << o + 1 << "): ";
            display(shead[o], stop[o]);
            cout << "Use 'Select a stack' to work on stack " << e + 1 << " or " << o + 1 << endl;
            break;
        }

        case 6:
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            cout << "Stack " << scur + 1 << ": ";
            display(h, t);
            nextGreater(h, t);
            break;

        case 7:
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            cout << "Before: ";
            display(h, t);
            sortList(h, t);
            cout << "After: ";
            display(h, t);
            break;

        case 8:
            cout << "Enter string: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Stack Overflow: string is longer than " << maxsize << " characters" << endl;
            else if (isPalindrome(s) == 1)
                cout << "Palindrome" << endl;
            else
                cout << "Not Palindrome" << endl;
            break;

        case 9:
        {
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            if (snum + 1 > MAXS)
            {
                cout << "No room for another stack" << endl;
                break;
            }
            int c = snum;               // the copy goes in a new stack
            createList(shead[c], 0);
            stop[c] = NULL;
            snum++;

            copyStack(h, t, shead[c], stop[c]);
            cout << "Original (stack " << scur + 1 << "): ";
            display(h, t);
            cout << "Copy (stack " << c + 1 << "): ";
            display(shead[c], stop[c]);
            break;
        }

        case 10:
            cout << "Enter brackets: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Stack Overflow: more than " << maxsize << " brackets" << endl;
            else if (isBalanced(s) == 1)
                cout << "true (Balanced)" << endl;
            else
                cout << "false (Not Balanced)" << endl;
            break;

        case 11:
            if (t == NULL)
            {
                cout << "Stack is empty, push some values first" << endl;
                break;
            }
            cout << "Before: ";
            display(h, t);
            removeDuplicates(h, t);
            cout << "After: ";
            display(h, t);
            break;

        case 12:
        {
            int a = 0, b = 0;
            cout << "First stack (1 to " << snum << "): ";
            cin >> a;
            cout << "Second stack (1 to " << snum << "): ";
            cin >> b;

            // Check 1: both numbers must be stacks that exist
            if (a < 1 || a > snum || b < 1 || b > snum)
            {
                cout << "Wrong stack number" << endl;
                break;
            }
            // Check 2: the two stacks must be different
            if (a == b)
            {
                cout << "Choose two different stacks" << endl;
                break;
            }
            a--;                        // user numbers start at 1, the array at 0
            b--;
            // Check 3: neither stack may be empty
            if (stop[a] == NULL)
            {
                cout << "Stack " << a + 1 << " is empty, push some values first" << endl;
                break;
            }
            if (stop[b] == NULL)
            {
                cout << "Stack " << b + 1 << " is empty, push some values first" << endl;
                break;
            }
            // Check 4: room for the result stack
            if (snum + 1 > MAXS)
            {
                cout << "No room for another stack" << endl;
                break;
            }

            int res = snum;             // the result goes in a new stack
            createList(shead[res], 0);
            stop[res] = NULL;
            snum++;

            intersection(shead[a], stop[a], shead[b], stop[b], shead[res], stop[res]);
            cout << "Stack " << a + 1 << ": ";
            display(shead[a], stop[a]);
            cout << "Stack " << b + 1 << ": ";
            display(shead[b], stop[b]);
            cout << "Intersection (stack " << res + 1 << "): ";
            display(shead[res], stop[res]);
            break;
        }

        case 13:
            if (snum >= MAXS)
            {
                cout << "No room for another stack" << endl;
                break;
            }
            createList(shead[snum], 0);
            stop[snum] = NULL;
            scur = snum;                // the new stack becomes the selected one
            snum++;
            cout << "Stack " << scur + 1 << " created and selected" << endl;
            break;

        case 14:
            cout << "Stack number (1 to " << snum << "): ";
            cin >> n;
            if (n < 1 || n > snum)
                cout << "Wrong stack number" << endl;
            else
            {
                scur = n - 1;
                cout << "Stack " << n << " selected: ";
                display(shead[scur], stop[scur]);
            }
            break;

        case 15:
            for (int i = 0; i < snum; i++)
            {
                cout << "Stack " << i + 1 << ": ";
                display(shead[i], stop[i]);
            }
            break;

        case 0:
            break;

        default:
            cout << "Wrong choice" << endl;
        }
    } while (ch > 0);
}

void func::queueMenu()
{
    int ch = 0, x = 0, n = 0;
    string s;
    do
    {
        // h, f and r are the head, front and rear of the selected queue
        node *&h = qhead[qcur];
        node *&f = qfront[qcur];
        node *&r = qrear[qcur];

        cout << "\n--- QUEUE " << qcur + 1 << " (of " << qnum << ") ---" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Display" << endl;
        cout << "4. Count" << endl;
        cout << "5. Reverse" << endl;
        cout << "6. Q1  Split into two queues (adds 2 new queues)" << endl;
        cout << "7. Q2  Even / Odd queues (adds 2 new queues)" << endl;
        cout << "8. Q3  Next greater element" << endl;
        cout << "9. Q5  Sort (bubble sort)" << endl;
        cout << "10. Q6 Palindrome check" << endl;
        cout << "11. Q7 Copy the queue (adds 1 new queue)" << endl;
        cout << "12. Q8 Balanced brackets" << endl;
        cout << "13. Q9 Remove duplicates" << endl;
        cout << "14. Q10 Intersection of two queues (adds 1 new queue)" << endl;
        cout << "15. Create a new queue" << endl;
        cout << "16. Select a queue" << endl;
        cout << "17. Show all queues" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Value: ";
            cin >> x;
            qpush(h, f, r, x);
            cout << "Queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            break;

        case 2:
            if (f == NULL)
                cout << "Queue Underflow" << endl;
            else
                cout << "Deleted: " << qpop(h, f, r) << endl;
            cout << "Queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            break;

        case 3:
            cout << "Queue " << qcur + 1 << " (front first): ";
            qdisplay(f, r);
            break;

        case 4:
            cout << "Count: " << qcount(f, r) << endl;
            break;

        case 5:
            qreverse(f, r);
            cout << "Queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            break;

        case 6:
        {
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            if (qnum + 2 > MAXS)
            {
                cout << "No room for two more queues" << endl;
                break;
            }
            // two new queues at the end of the array: a is the first half, b the second
            int a = qnum, b = qnum + 1;
            if (splitQueue(h, f, r, qhead[a], qfront[a], qrear[a], qhead[b], qfront[b], qrear[b]) == 0)
            {
                cout << "Queue has fewer than 2 nodes, it cannot be split" << endl;
                break;
            }
            qnum += 2;

            cout << "Whole queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            cout << "Queue " << a + 1 << " (first half): ";
            qdisplay(qfront[a], qrear[a]);
            cout << "Queue " << b + 1 << " (second half): ";
            qdisplay(qfront[b], qrear[b]);
            break;
        }

        case 7:
        {
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            if (qnum + 2 > MAXS)
            {
                cout << "No room for two more queues" << endl;
                break;
            }
            // two new queues at the end of the array: e for even, o for odd
            int e = qnum, o = qnum + 1;
            createList(qhead[e], 0);
            qfront[e] = NULL;
            qrear[e] = NULL;
            createList(qhead[o], 0);
            qfront[o] = NULL;
            qrear[o] = NULL;
            qnum += 2;

            qevenOdd(f, r, qhead[e], qfront[e], qrear[e], qhead[o], qfront[o], qrear[o]);
            cout << "Queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            cout << "Even queue (queue " << e + 1 << "): ";
            qdisplay(qfront[e], qrear[e]);
            cout << "Odd queue (queue " << o + 1 << "): ";
            qdisplay(qfront[o], qrear[o]);
            cout << "Use 'Select a queue' to work on queue " << e + 1 << " or " << o + 1 << endl;
            break;
        }

        case 8:
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Queue " << qcur + 1 << ": ";
            qdisplay(f, r);
            qnextGreater(f, r);
            break;

        case 9:
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            qdisplay(f, r);
            qsortList(f, r);
            cout << "After: ";
            qdisplay(f, r);
            break;

        case 10:
            cout << "Enter string: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Queue Overflow: string is longer than " << maxsize << " characters" << endl;
            else if (qisPalindrome(s) == 1)
                cout << "Palindrome" << endl;
            else
                cout << "Not Palindrome" << endl;
            break;

        case 11:
        {
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            if (qnum + 1 > MAXS)
            {
                cout << "No room for another queue" << endl;
                break;
            }
            int c = qnum;               // the copy goes in a new queue
            createList(qhead[c], 0);
            qfront[c] = NULL;
            qrear[c] = NULL;
            qnum++;

            copyQueue(f, r, qhead[c], qfront[c], qrear[c]);
            cout << "Original (queue " << qcur + 1 << "): ";
            qdisplay(f, r);
            cout << "Copy (queue " << c + 1 << "): ";
            qdisplay(qfront[c], qrear[c]);
            break;
        }

        case 12:
            cout << "Enter brackets: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Queue Overflow: more than " << maxsize << " brackets" << endl;
            else if (qisBalanced(s) == 1)
                cout << "true (Balanced)" << endl;
            else
                cout << "false (Not Balanced)" << endl;
            break;

        case 13:
            if (f == NULL)
            {
                cout << "Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            qdisplay(f, r);
            qremoveDuplicates(h, f, r);
            cout << "After: ";
            qdisplay(f, r);
            break;

        case 14:
        {
            int a = 0, b = 0;
            cout << "First queue (1 to " << qnum << "): ";
            cin >> a;
            cout << "Second queue (1 to " << qnum << "): ";
            cin >> b;

            // Check 1: both numbers must be queues that exist
            if (a < 1 || a > qnum || b < 1 || b > qnum)
            {
                cout << "Wrong queue number" << endl;
                break;
            }
            // Check 2: the two queues must be different
            if (a == b)
            {
                cout << "Choose two different queues" << endl;
                break;
            }
            a--;                        // user numbers start at 1, the array at 0
            b--;
            // Check 3: neither queue may be empty
            if (qfront[a] == NULL)
            {
                cout << "Queue " << a + 1 << " is empty, insert some values first" << endl;
                break;
            }
            if (qfront[b] == NULL)
            {
                cout << "Queue " << b + 1 << " is empty, insert some values first" << endl;
                break;
            }
            // Check 4: room for the result queue
            if (qnum + 1 > MAXS)
            {
                cout << "No room for another queue" << endl;
                break;
            }

            int res = qnum;             // the result goes in a new queue
            createList(qhead[res], 0);
            qfront[res] = NULL;
            qrear[res] = NULL;
            qnum++;

            qintersection(qfront[a], qrear[a], qfront[b], qrear[b], qhead[res], qfront[res], qrear[res]);
            cout << "Queue " << a + 1 << ": ";
            qdisplay(qfront[a], qrear[a]);
            cout << "Queue " << b + 1 << ": ";
            qdisplay(qfront[b], qrear[b]);
            cout << "Intersection (queue " << res + 1 << "): ";
            qdisplay(qfront[res], qrear[res]);
            break;
        }

        case 15:
            if (qnum >= MAXS)
            {
                cout << "No room for another queue" << endl;
                break;
            }
            createList(qhead[qnum], 0);
            qfront[qnum] = NULL;
            qrear[qnum] = NULL;
            qcur = qnum;                // the new queue becomes the selected one
            qnum++;
            cout << "Queue " << qcur + 1 << " created and selected" << endl;
            break;

        case 16:
            cout << "Queue number (1 to " << qnum << "): ";
            cin >> n;
            if (n < 1 || n > qnum)
                cout << "Wrong queue number" << endl;
            else
            {
                qcur = n - 1;
                cout << "Queue " << n << " selected: ";
                qdisplay(qfront[qcur], qrear[qcur]);
            }
            break;

        case 17:
            for (int i = 0; i < qnum; i++)
            {
                cout << "Queue " << i + 1 << ": ";
                qdisplay(qfront[i], qrear[i]);
            }
            break;

        case 0:
            break;

        default:
            cout << "Wrong choice" << endl;
        }
    } while (ch > 0);
}

void func::circularMenu()
{
    int ch = 0, x = 0, n = 0;
    string s;
    do
    {
        // h, f and r are the head, front and rear of the selected circular queue
        node *&h = chead[ccur];
        node *&f = cfront[ccur];
        node *&r = crear[ccur];

        cout << "\n--- CIRCULAR QUEUE " << ccur + 1 << " (of " << cnum << ") ---" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. Display" << endl;
        cout << "4. Count" << endl;
        cout << "5. Reverse" << endl;
        cout << "6. Q1  Split into two circular queues (adds 2 new circular queues)" << endl;
        cout << "7. Q2  Even / Odd circular queues (adds 2 new circular queues)" << endl;
        cout << "8. Q3  Next greater element (wraps around)" << endl;
        cout << "9. Q5  Sort (bubble sort)" << endl;
        cout << "10. Q6 Palindrome check" << endl;
        cout << "11. Q7 Copy the circular queue (adds 1 new circular queue)" << endl;
        cout << "12. Q8 Balanced brackets" << endl;
        cout << "13. Q9 Remove duplicates" << endl;
        cout << "14. Q10 Intersection of two circular queues (adds 1 new circular queue)" << endl;
        cout << "15. Create a new circular queue" << endl;
        cout << "16. Select a circular queue" << endl;
        cout << "17. Show all circular queues" << endl;
        cout << "0. Back" << endl;
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            cout << "Value: ";
            cin >> x;
            cpush(h, f, r, x);
            cout << "Circular Queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            break;

        case 2:
            if (f == NULL)
                cout << "Circular Queue Underflow" << endl;
            else
                cout << "Deleted: " << cpop(f, r) << endl;
            cout << "Circular Queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            break;

        case 3:
            cout << "Circular Queue " << ccur + 1 << " (front first): ";
            cdisplay(f, r);
            break;

        case 4:
            cout << "Count: " << ccount(f, r) << endl;
            break;

        case 5:
            creverse(f, r);
            cout << "Circular Queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            break;

        case 6:
        {
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            if (cnum + 2 > MAXS)
            {
                cout << "No room for two more circular queues" << endl;
                break;
            }
            // two new circular queues at the end of the array: a is the first half, b the second
            int a = cnum, b = cnum + 1;
            if (splitCircular(h, f, r, chead[a], cfront[a], crear[a], chead[b], cfront[b], crear[b]) == 0)
            {
                cout << "Circular queue has fewer than 2 nodes, it cannot be split" << endl;
                break;
            }
            cnum += 2;

            cout << "Whole circular queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            cout << "Circular queue " << a + 1 << " (first half): ";
            cdisplay(cfront[a], crear[a]);
            cout << "Circular queue " << b + 1 << " (second half): ";
            cdisplay(cfront[b], crear[b]);
            break;
        }

        case 7:
        {
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            if (cnum + 2 > MAXS)
            {
                cout << "No room for two more circular queues" << endl;
                break;
            }
            // two new circular queues at the end of the array: e for even, o for odd
            int e = cnum, o = cnum + 1;
            createList(chead[e], 1);
            cfront[e] = NULL;
            crear[e] = NULL;
            createList(chead[o], 1);
            cfront[o] = NULL;
            crear[o] = NULL;
            cnum += 2;

            cevenOdd(f, r, chead[e], cfront[e], crear[e], chead[o], cfront[o], crear[o]);
            cout << "Circular Queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            cout << "Even circular queue (circular queue " << e + 1 << "): ";
            cdisplay(cfront[e], crear[e]);
            cout << "Odd circular queue (circular queue " << o + 1 << "): ";
            cdisplay(cfront[o], crear[o]);
            cout << "Use 'Select a circular queue' to work on " << e + 1 << " or " << o + 1 << endl;
            break;
        }

        case 8:
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Circular Queue " << ccur + 1 << ": ";
            cdisplay(f, r);
            cnextGreater(f, r);
            break;

        case 9:
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            cdisplay(f, r);
            csortList(f, r);
            cout << "After: ";
            cdisplay(f, r);
            break;

        case 10:
            cout << "Enter string: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Circular Queue Overflow: string is longer than " << maxsize << " characters" << endl;
            else if (cisPalindrome(s) == 1)
                cout << "Palindrome" << endl;
            else
                cout << "Not Palindrome" << endl;
            break;

        case 11:
        {
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            if (cnum + 1 > MAXS)
            {
                cout << "No room for another circular queue" << endl;
                break;
            }
            int c = cnum;               // the copy goes in a new circular queue
            createList(chead[c], 1);
            cfront[c] = NULL;
            crear[c] = NULL;
            cnum++;

            copyCircular(f, r, chead[c], cfront[c], crear[c]);
            cout << "Original (circular queue " << ccur + 1 << "): ";
            cdisplay(f, r);
            cout << "Copy (circular queue " << c + 1 << "): ";
            cdisplay(cfront[c], crear[c]);
            break;
        }

        case 12:
            cout << "Enter brackets: ";
            cin >> s;
            if ((int)s.length() > maxsize)
                cout << "Circular Queue Overflow: more than " << maxsize << " brackets" << endl;
            else if (cisBalanced(s) == 1)
                cout << "true (Balanced)" << endl;
            else
                cout << "false (Not Balanced)" << endl;
            break;

        case 13:
            if (f == NULL)
            {
                cout << "Circular Queue is empty, insert some values first" << endl;
                break;
            }
            cout << "Before: ";
            cdisplay(f, r);
            cremoveDuplicates(h, f, r);
            cout << "After: ";
            cdisplay(f, r);
            break;

        case 14:
        {
            int a = 0, b = 0;
            cout << "First circular queue (1 to " << cnum << "): ";
            cin >> a;
            cout << "Second circular queue (1 to " << cnum << "): ";
            cin >> b;

            // Check 1: both numbers must be circular queues that exist
            if (a < 1 || a > cnum || b < 1 || b > cnum)
            {
                cout << "Wrong circular queue number" << endl;
                break;
            }
            // Check 2: the two circular queues must be different
            if (a == b)
            {
                cout << "Choose two different circular queues" << endl;
                break;
            }
            a--;                        // user numbers start at 1, the array at 0
            b--;
            // Check 3: neither circular queue may be empty
            if (cfront[a] == NULL)
            {
                cout << "Circular Queue " << a + 1 << " is empty, insert some values first" << endl;
                break;
            }
            if (cfront[b] == NULL)
            {
                cout << "Circular Queue " << b + 1 << " is empty, insert some values first" << endl;
                break;
            }
            // Check 4: room for the result circular queue
            if (cnum + 1 > MAXS)
            {
                cout << "No room for another circular queue" << endl;
                break;
            }

            int res = cnum;             // the result goes in a new circular queue
            createList(chead[res], 1);
            cfront[res] = NULL;
            crear[res] = NULL;
            cnum++;

            cintersection(cfront[a], crear[a], cfront[b], crear[b], chead[res], cfront[res], crear[res]);
            cout << "Circular Queue " << a + 1 << ": ";
            cdisplay(cfront[a], crear[a]);
            cout << "Circular Queue " << b + 1 << ": ";
            cdisplay(cfront[b], crear[b]);
            cout << "Intersection (circular queue " << res + 1 << "): ";
            cdisplay(cfront[res], crear[res]);
            break;
        }

        case 15:
            if (cnum >= MAXS)
            {
                cout << "No room for another circular queue" << endl;
                break;
            }
            createList(chead[cnum], 1);
            cfront[cnum] = NULL;
            crear[cnum] = NULL;
            ccur = cnum;                // the new circular queue becomes the selected one
            cnum++;
            cout << "Circular Queue " << ccur + 1 << " created and selected" << endl;
            break;

        case 16:
            cout << "Circular queue number (1 to " << cnum << "): ";
            cin >> n;
            if (n < 1 || n > cnum)
                cout << "Wrong circular queue number" << endl;
            else
            {
                ccur = n - 1;
                cout << "Circular Queue " << n << " selected: ";
                cdisplay(cfront[ccur], crear[ccur]);
            }
            break;

        case 17:
            for (int i = 0; i < cnum; i++)
            {
                cout << "Circular Queue " << i + 1 << ": ";
                cdisplay(cfront[i], crear[i]);
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
    // start with one of each kind, plus the temporary lists
    createList(shead[0], 0);
    snum = 1;
    createList(qhead[0], 0);
    qnum = 1;
    createList(chead[0], 1);    // circular: last node points back to first
    cnum = 1;

    createList(stmp, 0);
    createList(qtmp, 0);
    createList(ctmp, 1);

    int c = 0;
    do
    {
        cout << "\n===== MAIN MENU =====" << endl;
        cout << "1. Stack" << endl;
        cout << "2. Queue" << endl;
        cout << "3. Circular Queue" << endl;
        cout << "0. Exit" << endl;
        cout << "Choice: ";
        cin >> c;
        if (c == 1)
            stackMenu();
        else if (c == 2)
            queueMenu();
        else if (c == 3)
            circularMenu();
    } while (c > 0);
}
