#include <iostream>
using namespace std;
struct node { int data; node *next; };
void qreverseLinks(node *&head, node *&f, node *&r)
{
    if (f == NULL || f == r) return;
    node *rest = r->next;
    node *prev = rest;
    node *cur = f;
    while (cur != rest)
    {
        node *q = cur->next;
        cur->next = prev;
        prev = cur;
        cur = q;
    }
    r = f;
    f = prev;
    head = f;
}
void show(node *f, node *r){ if(!f){cout<<"empty\n";return;} node*e=r->next; for(node*p=f;p!=e;p=p->next)cout<<p->data<<" "; cout<<endl;}
int main(){
  for (int used = 0; used <= 6; used++) {
    node *n[6]; for(int i=0;i<6;i++){n[i]=new node{0,NULL};} for(int i=0;i<5;i++)n[i]->next=n[i+1];
    node *head=n[0],*f=NULL,*r=NULL;
    if(used>0){f=head; for(int i=0;i<used;i++){n[i]->data=(i+1)*10; r=n[i];}}
    cout<<"used="<<used<<": "; show(f,r);
    qreverseLinks(head,f,r);
    cout<<"        after: "; show(f,r);
    if(used>0){ int c=0; for(node*p=head;p;p=p->next)c++; cout<<"        nodes in list="<<c<<" head==f? "<<(head==f)<<" r->next "<<(r->next?"free":"NULL")<<endl; }
  }
}
