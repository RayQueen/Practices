#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Dada  una  lista  con  arreglos  de  enteros  y  número  entero  n,  implementar  
una  función  donde  se  eliminen  todos  los números n de la lista.*/

void deleteN(int n, DLList<int>* lista){
    Node<int>* p=lista->first();
    if(p==nullptr)return;
    while(p!=nullptr){
        if(p->payload==n){
            Node<int>* aux=p;
            lista->next(p);
            lista->remove(aux);
        }else{
            lista->next(p);
        }
    }
}

int main(){
    DLList<int> lista;
    lista.postInsert(lista.first(), 1);
    Node<int>* p=lista.first();
    lista.postInsert(p, 2);
    lista.next(p);
    lista.postInsert(p, 3);

    printList(lista);
    cout<<endl;
    deleteN(2, &lista);
    printList(lista);
    cout<<endl;
    deleteN(3, &lista);
    printList(lista);

    return 0;
}