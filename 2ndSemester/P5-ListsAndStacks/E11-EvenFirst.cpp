#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Dada  una  lista  de  números  enteros  ordenada  ascendentemente, realice  
una  función  que  retorne  una  lista  con  los elementos pares al comienzo 
de la lista y los impares al final (De manera ordenada igualmente).*/

void parPrimero(DLList<int> &A, DLList<int> &B){
    Node<int>*i=A.last();
    Node<int>*lastEven=B.first();
    while(i!=nullptr){
        if(i->payload%2==0){
            B.preInsert(B.first(),i->payload);
            if(B.getCounter()==1){
                lastEven=B.first();    
            }
        }else{
            B.postInsert(lastEven,i->payload);
        }
        A.prev(i);
    }
}

int main(){
    DLList<int> A, B;

    A.postInsert(A.last(), 1);
    A.postInsert(A.last(), 2);
    A.postInsert(A.last(), 3);
    A.postInsert(A.last(), 4);
    A.postInsert(A.last(), 5);
    A.postInsert(A.last(), 6);

    printList(A);
    cout<<endl;
    printList(B);

    parPrimero(A,B);

    cout<<endl;
    printList(B);

    return 0;
}