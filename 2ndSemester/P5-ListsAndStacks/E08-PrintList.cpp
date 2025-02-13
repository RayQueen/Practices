#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Realice una función ‘imprime’ utilizando apuntadores que 
imprima una lista L dada por parámetro a la función.*/

template <typename T>
void listPrint(DLList<T> &list){
    Node<T>* p=list.first();
    int i=1;
    while(p!=nullptr){
        cout<<"Nodo ["<<i<<"]: "
        <<p->payload<<endl;
        i++;
        list.next(p);
    }
    if(i==1){
        cout<<"Lista vacia."<<endl;
    }
}

int main(){
    DLList<char> A, C;
    A.postInsert(A.last(), 'a');
    A.postInsert(A.last(), 'b');
    A.postInsert(A.last(), 'c');
    A.postInsert(A.last(), 'd');
    A.postInsert(A.last(), 'e');
    A.postInsert(A.last(), 'f');
    A.postInsert(A.last(), 'g');

    DLList<int> B;

    B.postInsert(B.last(), 1);
    B.postInsert(B.last(), 2);
    B.postInsert(B.last(), 3);
    B.postInsert(B.last(), 4);
    B.postInsert(B.last(), 5);
    B.postInsert(B.last(), 6);

    listPrint(A);
    cout<<endl;
    listPrint(B);
    cout<<endl;
    listPrint(C);

    return 0;
}