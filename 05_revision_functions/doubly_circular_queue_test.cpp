#include <iostream>
using namespace std;
struct node { int data; node *next; node *prev; };
void dcpush(node *head, node *&f, node *&r, int x)
{
    if (f == NULL && r == NULL) { f = head; r = head; r->data = x; return; }
    if (f == head && r->next == head) { cout << "Queue Overflow" << endl; return; }
    if (r->next == f) { cout << "Circular Queue Overflow" << endl; return; }
    if (r->next == head) r = head; else r = r->next;
    r->data = x;
}
int dcpop(node *&f, node *&r)
{
    if (f == NULL) { cout << "Circular Queue Underflow" << endl; return -1; }
    int x = f->data;
    if (f == r) { f = NULL; r = NULL; return x; }
    f = f->next;
    return x;
}
int dccount(node *f, node *r)
{
    if (f == NULL) return 0;
    int c = 0; node *p = f; node *end = r->next;
    do { c++; p = p->next; } while (p != end);
    return c;
}
int dcsearch(node *f, node *r, int x)
{
    if (f == NULL) return 0;
    node *p = f; node *end = r->next;
    do { if (p->data == x) return 1; p = p->next; } while (p != end);
    return 0;
}
void dcreverse(node *f, node *r)
{
    int n = dccount(f, r);
    node *a = f; node *b = r;
    for (int i = 0; i < n / 2; i++)
    { int t = a->data; a->data = b->data; b->data = t; a = a->next; b = b->prev; }
}
void dcdisplay(node *f, node *r)
{
    if (f == NULL) { cout << "empty" << endl; return; }
    node *p = f; node *end = r->next;
    do { cout << p->data << " "; p = p->next; } while (p != end);
    cout << endl;
}
void dcdisplayBack(node *f, node *r)
{
    if (f == NULL) { cout << "empty" << endl; return; }
    node *p = r; node *end = f->prev;
    do { cout << p->data << " "; p = p->prev; } while (p != end);
    cout << endl;
}
int main(){
  node *n[6]; for(int i=0;i<6;i++) n[i]=new node{0,NULL,NULL};
  for(int i=0;i<6;i++){ n[i]->next=n[(i+1)%6]; n[i]->prev=n[(i+5)%6]; }
  node *head=n[0],*f=NULL,*r=NULL;
  cout<<"pop empty: "; dcpop(f,r);
  for(int i=1;i<=6;i++) dcpush(head,f,r,i*10);
  cout<<"full: "; dcdisplay(f,r); dcdisplayBack(f,r);
  dcpush(head,f,r,99);
  cout<<"count="<<dccount(f,r)<<" search30="<<dcsearch(f,r,30)<<" search99="<<dcsearch(f,r,99)<<endl;
  dcpop(f,r); dcpop(f,r); dcpop(f,r);
  cout<<"after 3 pops: "; dcdisplay(f,r);
  dcpush(head,f,r,70); dcpush(head,f,r,80);   // rear wraps
  cout<<"wrapped: "; dcdisplay(f,r); dcdisplayBack(f,r);
  cout<<"count="<<dccount(f,r)<<endl;
  dcreverse(f,r);
  cout<<"reversed: "; dcdisplay(f,r); dcdisplayBack(f,r);
  dcpush(head,f,r,1); dcpush(head,f,r,2);
  cout<<"full again: "; dcdisplay(f,r);
  dcpush(head,f,r,3);
  while(f) dcpop(f,r);
  cout<<"drained: "; dcdisplay(f,r);
  dcpush(head,f,r,5); cout<<"restart: "; dcdisplay(f,r);
  dcreverse(f,r); dcdisplay(f,r);
}
