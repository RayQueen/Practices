#include <iostream>
#include "SimpleLinkedList.cpp"
using namespace std;

/*  Elabore dos algoritmos (uno recursivo y otro iterativo) en el cual dada 
una lista lineal en forma enlazada la invierta, sin crear una nueva lista, 
ni mover los elementos físicamente de la lista. */

//Sin alterar los payloads

template <typename T>
void rInversePun(SLList<T> &list, Node<T>* f, Node<T>* p){
    Node<T>* l=p;
    if(p==f){
        p->next=nullptr;
        return;
    }
    p->next=list.findPrev(p);
    rInversePun(list, f, p->next);
    list.changeHead(l);
    return;
}

template <typename T>
void iInversePun(SLList<T> &list){
    Node<T>* p=list.findPrev(list.last());
    Node<T>* f=list.first();
    Node<T>* l=p;
    while(p!=f){
        p->next=list.findPrev(p);
        p=p->next;
    }
    list.changeHead(l);
    p->next=nullptr;
        return;
}

template <typename T>
void rInversePun(SLList<T> &list){
    rInversePun(list, list.first(), list.findPrev(list.last()));
}

//Sin alterar los punteros

template <typename T>
void swap(Node<T>* a, Node<T>* b){
    T aux=a->payload;
    a->payload=b->payload;
    b->payload=aux;
}

template <typename T>
void rInversePay(SLList<T> &list, Node<T>* li, Node<T>* ls){
    if(list.findPrev(li)==ls || li==ls) return;
    swap(li,ls);
    list.next(li);
    rInversePay(list, li, list.findPrev(ls));
    return;
}

template <typename T>
void iInversePay(SLList<T> &list){
    Node<T>* li=list.first();
    Node<T>* ls=list.findPrev(list.last());
    while(list.findPrev(li)!=ls && li!=ls){
        swap(li,ls);
        list.next(li);
        ls=list.findPrev(ls);
    }
}

template <typename T>
void rInversePay(SLList<T> &list){
    rInversePay(list, list.first(), list.findPrev(list.last()));
}

void declareList(SLList<int> &A){
    A.insert(A.first(), 1);
    A.insert(A.first(), 2);
    A.insert(A.first(), 3);
    A.insert(A.first(), 4);
    A.insert(A.first(), 5);
    A.insert(A.first(), 6);
    A.insert(A.first(), 7);

    printList(A);
}

int main(){
    SLList<int> A;
    declareList(A);

    //Sin alterar los payloads
    rInversePun(A);
    printList(A);

    iInversePun(A);
    printList(A);

    //Sin alterar los punteros
    rInversePay(A);
    printList(A);

    iInversePay(A);
    printList(A);

    return 0;
}