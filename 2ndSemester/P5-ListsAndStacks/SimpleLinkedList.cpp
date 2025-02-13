#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
    T payload;
    Node *next;

    Node(T value): payload(value), next(nullptr) {} 
};

template <typename T>
class SLList{ //Simple linked list
    private:
    Node<T>* head;
    int counter;

    public:
    SLList(): head(nullptr), counter(0) {} //Constructor

    ~SLList(){ //Destructor
        while(!isEmpty()){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty(){ //La lista esta vacia?
        return(head==nullptr);
    }

    int getCounter(){
        return counter;
    }

    void changeHead(Node<T>* newHead){
        this->head=newHead;
    }

    Node<T>* first(){return head;}
    Node<T>* last(){return nullptr;}

    T* get(Node<T>* p){
        if (p==nullptr) return nullptr;
        return &p->payload; //Retornamos la direccion porque T es un puntero
    }

    void next(Node<T>* &p){
        if(p==nullptr) return;
        p=p->next;
    }

    Node<T>* findPrev(Node<T>* p){
        Node<T>* i=first();
        while(i!=last()){
            if(i->next==p)return i;
            next(i);
        }
        return i;
    }

    void insert(Node<T>* p, T valid){
        Node<T>* newNode = new Node<T>(valid);
        newNode->next=p;
        counter++;
        if(p==first()||isEmpty()){
            head=newNode;
            return;
        }
        Node<T>* prev= findPrev(p);
        prev->next=newNode;
    }

    void remove(Node<T>* p){
        Node<T>* prev = findPrev(p);
        prev->next=p->next;
        counter--;
        delete p;
    }
};

// Print the contents of the list
template <typename T>
void printList(SLList<T> &myList) {
    Node<T>* listIterator = myList.first();
    int nodeIndex = 1;
    int listCounter = myList.getCounter();
    if(listCounter==0){
        cout<<"Empty List."<<endl;
        return;
    }
    for(; nodeIndex <= listCounter; nodeIndex++) {
        T retrievedData = *(myList.get(listIterator));
        cout << "Node " << nodeIndex << ": [" << retrievedData << "]" << endl;
        myList.next(listIterator);
    }
    cout<<endl;
};