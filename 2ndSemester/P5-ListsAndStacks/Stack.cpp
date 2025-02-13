#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

template <typename T>
class Stack: private DLList<T>{
    public:
    Stack(): DLList<T>::DLList<T>() {};

    bool isEmpty(){
        return DLList<T>::isEmpty();
    }

    int getCounter(){
        return DLList<T>::getCounter();
    }

    void push(T valid){
        DLList<T>::preInsert(DLList<T>::first(), valid);
    }

    T* first(){
        if(this->isEmpty()) return nullptr;
        return &(DLList<T>::first()->payload);
    }

    T pop(){
        T x=DLList<T>::first()->payload;
        DLList<T>::remove(DLList<T>::first());
        return x;
    }

    void printStack() {
        Node<T>* listIterator = DLList<T>::first();
        int nodeIndex = 1;
        int listCounter = DLList<T>::getCounter();
        if(listCounter==0){
            cout<<"Empty List."<<endl;
            return;
        }
        for(; nodeIndex <= listCounter; nodeIndex++) {
            T retrievedData = *(DLList<T>::get(listIterator));
            cout << "Node " << nodeIndex << ": [" << retrievedData << "]" << endl;
            DLList<T>::next(listIterator);
        }
        cout<<endl;
    }
};

