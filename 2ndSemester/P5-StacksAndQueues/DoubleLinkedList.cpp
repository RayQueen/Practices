#include <iostream>
using namespace std;

template <typename T>
class Node{
    public:
    T payload;
    Node *next;
    Node *prev;

    Node(T value): payload(value), next(nullptr), prev(nullptr) {} 
};

template <typename T>
class DLList{ //Simple linked list
    private:
    Node<T>* head;
    Node<T>* tail;

    public:
    DLList(): head(nullptr), tail(nullptr) {} //Constructor por defecto

    // Constructor de copia
    DLList(const DLList& other) : head(nullptr), tail(nullptr) {
        Node<T>* current = other.head;
        while (current != nullptr) {
            postInsert(tail, current->payload);
            current = current->next;
        }
    }

    ~DLList(){ //Destructor
        while(!isEmpty()){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool isEmpty(){ //La lista esta vacia?
        return(head==nullptr);
    }

    Node<T>* first(){return head;}
    Node<T>* last(){return tail;}

    T* get(Node<T>* p){
        if (p==nullptr) return nullptr;
        return &p->payload; //Retornamos la direccion porque T es un puntero
    }

    void next(Node<T>* &p){
        if(p==nullptr) return;
        p=p->next;
    }

    void prev(Node<T>* &p){
        if(p==nullptr) return;
        p=p->prev;
    }

    void remove(Node<T>* p){
        if(p==nullptr) return;
        if(p->prev!=nullptr) p->prev->next=p->next;
        if(p->next!=nullptr) p->next->prev=p->prev;
        if(p==head) head=p->next;
        if(p==tail) tail=p->prev;
        delete p;
    }

    void preInsert(Node<T>* p, T valid){
        Node<T>* newNode = new Node<T>(valid);
        if(p==head) head=newNode;
        newNode->next=p;
        if(p==nullptr) return;
        newNode->prev=p->prev;
        if(p->prev!=nullptr) p->prev->next=newNode;
    }

    void postInsert(Node<T>* p, T valid){
        Node<T>* newNode = new Node<T>(valid);
        if(p==last()) tail=newNode;
        if(first()==nullptr) head=newNode;
        newNode->prev=p;
        if(p==nullptr) return;
        newNode->next=p->next;
        if(p->next!=nullptr) p->next->prev=newNode;
        p->next=newNode;
    }
};

// Print the contents of the list
template <typename T>
void printList(DLList<T> &myList) {
    Node<T>* listIterator = myList.first();
    int nodeIndex = 1;
    while (listIterator != nullptr) {
        T retrievedData = *myList.get(listIterator);
        std::cout << "Node " << nodeIndex << ": [" << retrievedData << "]" << std::endl;
        myList.next(listIterator);
        nodeIndex++;
    }
};