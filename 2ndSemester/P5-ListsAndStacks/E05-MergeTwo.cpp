#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Implementar una función mezcla2 que tenga como parámetros dos listas con arreglos 
de enteros ordenados de menor a  mayor  y  que  devuelva  una  nueva  lista  con  
arreglo  con  la  unión  de  ambas  listas  anteriores  con  sus  elementos 
ordenados de la misma forma.*/

void mezcla2(DLList<int> &A, DLList<int> &B, DLList<int> &C){
    Node<int>* a = A.first();
    Node<int>* b = B.first();
    if(a->payload<b->payload){
        C.postInsert(C.first(), a->payload);
        A.next(a);
    }else{
        C.postInsert(C.first(), b->payload);
        B.next(b);
    }
    Node<int>* c = C.first();
    while(a!=nullptr||b!=nullptr){
        if(a!=nullptr){
            if(b==nullptr){
                C.postInsert(c, a->payload);
                A.next(a);
            }else if(a->payload<b->payload){
                C.postInsert(c, a->payload);
                A.next(a);
            }else{
                C.postInsert(c, b->payload);
                B.next(b);
            }
        }else{
            C.postInsert(c, b->payload);
            B.next(b);
        }
        C.next(c);
    }
}

int main(){
    DLList<int> A, B, C;

    A.postInsert(A.first(), 1);
    Node<int>* a=A.first();
    A.postInsert(a, 3);
    A.next(a);
    A.postInsert(a, 3);
    A.next(a);
    A.postInsert(a, 5);

    B.postInsert(B.first(), 0);
    Node<int>* b=B.first();
    B.postInsert(b, 2);
    B.next(b);
    B.postInsert(b, 6);
    B.next(b);
    B.postInsert(b, 9);

    mezcla2(A,B,C);

    cout<<"Lista A:"<<endl;
    printList(A);
    cout<<endl<<"Lista B:"<<endl;
    printList(B);
    cout<<endl<<"Lista C:"<<endl;
    printList(C);

    return 0;
}