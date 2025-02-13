#include <iostream>
#include "SimpleLinkedList.cpp"
using namespace std;

/*Cree una función que elimine de una lista simplemente 
enlazada de enteros, los valores repetidos.*/

Node<int>* repeated(Node<int>*v, SLList<int> &list){
    Node<int>* p=list.first();
    while(p!=nullptr){
        if(p!=v && p->payload==v->payload) return p;
        list.next(p);
    }
    return nullptr;
}

void removeRep(SLList<int> &list){
    Node<int>* i=list.first();
    Node<int>* p;
    while(i!=nullptr){
        p = repeated(i, list);
        if(p!=nullptr){
            list.remove(p);
        }
        list.next(i);
    }
}

int main(){
    SLList<int> A;

    A.insert(A.first(), 1);
    A.insert(A.first(), 2);
    A.insert(A.first(), 3);
    A.insert(A.first(), 4);
    A.insert(A.first(), 3);
    A.insert(A.first(), 4);

    printList(A);
    cout<<endl;

    removeRep(A);

    printList(A);

    return 0;
}