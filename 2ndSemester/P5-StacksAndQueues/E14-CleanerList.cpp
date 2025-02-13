#include <iostream>
#include "SimpleLinkedList.cpp"
using namespace std;

/*Dada  una  lista  A  (desordenada  y  con  elementos  repetidos)  se  quiere  
que  usted  resuelva  de  manera  eficiente  el siguiente requerimiento: Obtener 
una lista B que contenga los elementos que están en A sin repeticiones, seguidos 
por el número de ocurrencias. Resuelva el problema utilizando manejo de apuntadores. 
La lista A puede ser modificada.*/

template <typename T>
bool repeated(T v, SLList<T> &B){
    Node<T>* i=B.first();
    while(i!=nullptr){
        if(v==i->payload) return true;
        B.next(i);
    }
    return false;
}

template <typename T>
void cleanCopy(SLList<T> &A, SLList<T> &B){
    Node<T>* i=A.findPrev(A.last());
    while(i!=nullptr){
        if(!repeated(i->payload, B)){
            B.insert(B.first(),i->payload);
        }
        i=A.findPrev(i);
    }
}

template <typename T>
void swap(Node<T>* a, Node<T>* b){
    T aux=a->payload;
    a->payload=b->payload;
    b->payload=aux;
}

template <typename T>
void arrange(SLList<T> &B, Node<T>* li, Node<T>* ls){
    if(B.findPrev(li)==ls) return;
    int listSize=B.getCounter();
    Node<T>* i=li;
    Node<T>* lastIndex=li;
    while(i!=ls){
        if(i->payload<ls->payload){
            swap(i,lastIndex);
            B.next(lastIndex);
        }
        B.next(i);
    }
    swap(lastIndex,ls);
    arrange(B, li, B.findPrev(lastIndex));
    arrange(B, lastIndex->next, ls);
}

template <typename T>
void cleanList(SLList<T> &A, SLList<T> &B){
    cleanCopy(A, B);
    Node<T>* ls=B.findPrev(B.last());
    arrange(B, B.first(), ls);
}

int main(){
    SLList<int> A, B;

    A.insert(A.first(), 3);
    A.insert(A.first(), 7);
    A.insert(A.first(), 4);
    A.insert(A.first(), 1);
    A.insert(A.first(), 1);
    A.insert(A.first(), 2);
    A.insert(A.first(), 3);
    A.insert(A.first(), 7);
    A.insert(A.first(), 6);
    A.insert(A.first(), 5);

    cout<<"Lista A: "<<endl;
    printList(A);
    cout<<endl;
    cout<<"Lista B: "<<endl;
    printList(B);
    cout<<endl;

    cleanList(A, B);

    cout<<"Lista B: "<<endl;
    printList(B);
    cout<<endl;

    return 0;
}