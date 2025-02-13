#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Realice una función ‘suma’ que retorne la suma de todos 
los elementos de una lista dada por parámetro. */

int suma(DLList<int> &list){
    Node<int>* p=list.first();
    int sum=0;
    while(p!=nullptr){
        sum+=p->payload;
        list.next(p);
    }
    return sum;
}

int main(){
    DLList<int> B;

    B.postInsert(B.last(), 1);
    B.postInsert(B.last(), 2);
    B.postInsert(B.last(), 3);
    B.postInsert(B.last(), 4);
    B.postInsert(B.last(), 5);
    B.postInsert(B.last(), 6);

    printList(B);

    cout<<endl<<suma(B)<<endl;

    return 0;
}