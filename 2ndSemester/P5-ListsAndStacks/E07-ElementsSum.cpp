#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Construir una función que sume los elementos de una lista con arreglos de manera 
recursiva, donde el algoritmo sea llamado: tamañoListaArreglo/2 veces.*/

int llamadas=0;

int sumaLista(DLList<int> A, Node<int>* li, Node<int>* ls){
    llamadas++;
    if(li->next==ls->prev) return li->payload+ls->payload+li->next->payload;
    if(li==ls->prev) return li->payload+ls->payload;
    return (li->payload+ls->payload+sumaLista(A, li->next, ls->prev));
}

int main(){
    DLList<int> A;

    A.postInsert(A.last(), 1);
    A.postInsert(A.last(), 2);
    A.postInsert(A.last(), 3);
    A.postInsert(A.last(), 4);
    A.postInsert(A.last(), 5);
    A.postInsert(A.last(), 6);

    printList(A);

    cout<<"Suma de todos los elementos en la lista: ";
    cout<<sumaLista(A, A.first(), A.last())<<endl;

    cout<<"Cantidad de llamadas a la funcion: ";
    cout<<llamadas<<endl;

    return 0;
}
