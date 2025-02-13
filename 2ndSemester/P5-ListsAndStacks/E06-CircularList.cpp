#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

/*Implemente una lista con arreglo que simule una lista circular de caracteres con n 
posiciones y dados dos enteros m e i, imprima m valores a partir de la posición i.*/

template <typename T>
class CList: private DLList<T>{
    public:

    int getCounter(){
        return DLList<T>::getCounter();
    }

    bool isEmpty(){
        return DLList<T>::isEmpty();
    }

    Node<T>* first(){
        return DLList<T>::first();
    }

    T get(Node<T>* p){
        return *(DLList<T>::get(p));
    }

    void next(Node<T>* &p){
        DLList<T>::next(p);
    }

    void add(T valid){
        DLList<T>::postInsert(DLList<T>::last(), valid);
        DLList<T>::last()->next=DLList<T>::first();
    }
};

template <typename T>
void printList(CList<T> &myList) {
    Node<T>* listIterator = myList.first();
    int nodeIndex = 1;
    int listCounter = myList.getCounter();
    for(; nodeIndex <= listCounter; nodeIndex++) {
        T retrievedData = myList.get(listIterator);
        cout << "Node " << nodeIndex << ": [" << retrievedData << "]" << endl;
        myList.next(listIterator);
    }
};

void imprimirCList(int m, int i, CList<char> &list){
    Node<char>* p = list.first();
    while(i>1){
        list.next(p);
        i--;
    }
    for (int j = 0; j < m; j++){
        cout<<p->payload<<endl;
        list.next(p);
    }
}

int main(){
    CList<char> A;
    A.add('a');
    A.add('b');
    A.add('c');
    A.add('d');
    A.add('e');
    A.add('f');
    A.add('g');

    printList(A);

    imprimirCList(8, 6, A);

    return 0;
}