#include <iostream>
#include "DoubleLinkedList.cpp"
using namespace std;

template <typename T>
class GTNode { //General Tree Node
    public:
    T value; //Valor del nodo
    DLList<GTNode*> children; //Hijos del actual nodo
    int childrenCount; //Numero actual de hijos

    GTNode(T value){ //Constructor
        this->childrenCount=0;
        this->value=value;
    }

    bool isLeaf(){ //Verifica si es hoja
        return children.isEmpty();
    }

    ~GTNode(){ //Destructor
        while(!children.isEmpty()){
            delete children.first()->payload;
            childrenCount--;
            children.remove(children.first());
        }
    }
};

template <typename T>
class GTree { //General tree
    public:
    GTNode<T> root; //Raiz del arbol

    GTree(T rootValue):root(rootValue){} //Constructor

    void addChildren(T value, GTNode<T>* parent){ //Añade hijos al arbol
        if(parent == NULL) return;

        GTNode<T>* newChild = new GTNode<T>(value);

        parent->children.postInsert(parent->children.last(), newChild);
        parent->childrenCount++;
    }
};

template <typename T>
class BTNode { //Binary tree node
    public:
    
    T value;
    BTNode<T>* leftChild; //Hijo izquierdo
    BTNode<T>* rightChild; //Hijo derecho
    
    BTNode(){ //Constructor
        this->value=0;
        leftChild=rightChild=NULL;
    }

    BTNode(T value){
        this->value=value;
        leftChild=rightChild=NULL;
    }
    
    ~BTNode(){
        if (leftChild != NULL) delete leftChild;
        if (rightChild != NULL) delete rightChild;
    }
    
    bool isLeaf(){
        return (leftChild==NULL && rightChild==NULL);
    }
    
    /*
    * Sobrecarga del operador <<, por la definicion del operador, recibe dos parametros, 
    * el primero es el stream donde se agrega el texto que se escribe, 
    * el segundo es el objeto que se escribe.
    * 
    * Ya que el operador trabaja sobre un parametro, si queremos acceder a los atributos privados del objeto necesitamos hacer que el operador sea friend de la clase,
    * de lo contrario solo se podra utilizar los atributos y metodos publicos del objeto que se pasa por parametro
    */
   friend ostream& operator<<(ostream& out, BinaryTreeNode &object) {
       out << "BinaryNode Payload: " << object.value;
       
       out << " Left Child: ";
       if (object.leftChild) out << object.leftChild->value;
       else out << "null";
       
       out << " Right Child: ";
       if (object.rightChild) out << object.rightChild->value;
       else out << "null";
       
       return out;
    }

    /* Se sobreescribe el operador para que funcione con punteros tambien */
    friend ostream& operator<<(ostream& out, BinaryTreeNode* &object) {
        if (object == NULL) {
            out << "null";
            return out;
        }
        
        out << "BinaryNode Payload: " << object->value;
        
        out << " Left Child: ";
        if (object->leftChild) out << object->leftChild->value;
        else out << "null";
        
        out << " Right Child: ";
        if (object->rightChild) out << object->rightChild->value;
        else out << "null";
        
        return out;
    }
};

template <typename T>
class BSTree { //Binary search tree
    public:
    BTNode<T>* root; //Raiz del arbol
    
    SearchBinaryTree() { //Constructor
        root = NULL;
    }
    
    void insert(T value) {
        insert(value, root);
    }
    
    bool found(T value) {
        found(value, root);
    }
    
    private:
    void insert(T value, BTNode<T>* &root) {
        if (root == NULL) {
            root = new BTNode<T>(value);
            return;
        }
        
        if (root->value == value) return;
        
        if (root->value < value) return insert(value, root->rightChild);
        
        insert(value, root->leftChild);
    }
    
    bool found(T value, BTNode<T>* root) {
        if (root == NULL) return false;
        
        if (root->value == value) return true;
        
        if (root->value < value) return found(value, root->rightChild);
        
        return found(value, root->leftChild);
    }
};

template <typename T>
class Heap {

private:
    T* data;
    int elementCount;
    int actualSize;
    const int resizeStep;

    void resizeArray(int newSize) {
        T* newData = new T[newSize];
        
        /* 
        * Esta instruccion copia la memoria de data a newData.
        * El tercer parametro es la cantidad de bytes a copiar, 
        * que serian los elementos actuales del arreglo* el tamanio de un elemento
        */ 
        memcpy(data, newData, elementCount * sizeof(T));
        // limpio el arreglo previo
        delete[]data;
        // Ahora copio la direccion del nuevo arreglo
        data = newData;
        actualSize = newSize;
    }

    int getLeftChildIndex(int parentIndex) {
        return parentIndex * 2 + 1;
    }

    int getRightChildIndex(int parentIndex) {
        return parentIndex * 2 + 2;
    }

    int getParentIndex(int childIndex) {
        return (childIndex - 1) / 2;
    }
    
    // Implementa un heap donde la raiz es siempre el maximo
    bool isHeap(int parentIndex) {
        if (parentIndex < 0) return true;
        int leftIndex = getLeftChildIndex(parentIndex);
        int rightIndex = getRightChildIndex(parentIndex);

        if (leftIndex < elementCount && data[parentIndex] < data[leftIndex]) return false;
        if (rightIndex < elementCount && data[parentIndex] < data[rightIndex]) return false;

        return true;
    }

    void swap(int indexA, int indexB) {
        T aux = data[indexA];
        data[indexA] = data[indexB];
        data[indexB] = aux;
    }

    void sinkValue(int parentIndex) {
        if (isHeap(parentIndex)) return;

        int leftChild = getLeftChildIndex(parentIndex);
        int rightChild = getRightChildIndex(parentIndex);

        int maxIndex = data[leftChild] > data[rightChild] ? leftChild : rightChild;

       swap(maxIndex, parentIndex);
       
       // Si el arbol tiene mas elementos sigo, sino me detengo
       if (maxIndex < elementCount - 1) sinkValue(maxIndex);
    }

    void floatValue(int childIndex) {
        int parentIndex = getParentIndex(childIndex);

        if (isHeap(parentIndex)) return;

        swap(childIndex, parentIndex);

        // Si no llegue a la raiz, sigo, sino me detengo
        if (parentIndex > 0) floatValue(parentIndex);
    }

public:
    Heap(const int resizeStep=16):resizeStep(resizeStep) {
        elementCount = 0;
        data = new T[resizeStep];
        actualSize = resizeStep;
    }

    ~Heap() {
        delete[]data;
    }

    T top() {
        T topValue = data[0];
        data[0] = data[elementCount - 1];
        elementCount--;
        // Verifico si al eliminar el nuevo elemento deberia hacer mas pequenio mi arreglo de datos
        if (actualSize - elementCount > resizeStep) resizeArray(actualSize - resizeStep);

        sinkValue(0);

        return topValue;
    }

    void insert(T x) {
        if (elementCount + 1 > actualSize) resizeArray(actualSize + resizeStep);

        data[elementCount] = x;
        elementCount++;
        floatValue(elementCount - 1);
    }

    bool isEmpty() {
        return elementCount <= 0;
    }

    void mezclar(Heap<T> x) {
        while (!x.isEmpty()) {
            T y = x.top();
            insert(y);
        }
    }

    void mezclarSinDuplicados(Heap<T> x) {
        while (!x.isEmpty()) {
            T y = x.top();
            Heap aux;
            while (!isEmpty()) {
                T z = top();
                if (z == y) break;
                aux.insert(z);
            }
            insert(y);
            while (!aux.isEmpty()) insert(aux.top());
        }
    }

    /* Se sobreescribe el operador para que funcione con punteros tambien */
    friend ostream& operator<<(ostream& out, Heap& object) {
        out << "Data: ";
        for (int i = 0; i < object.elementCount; i++) out << object.data[i] << "; ";
        out << endl;
        out << "Element Count: " << object.elementCount << ", Capacity: " << object.actualSize;
        return out;
    }
};

template <typename T>
bool isACompleteTree(GTNode<T>* root, int maxChildrenSize = -1){ //Determina si es un arbol completo
    if(root==NULL) return true;
    if(root->isLeaf()) return true;

    Node<GTNode<T>*>* p = root->children.first();
    int childrenCount = 0;

    while(p!=NULL){
        p=p->next;
        childrenCount++;
    }

    if (maxChildrenSize > 0 && childrenCount != maxChildrenSize) return false;

    p = root->children.first();

    while (p != NULL) {
        if (!isACompleteTree(p->payload, childrenCount)) return false;
        p = p->next;
    }

    return true;
}

template <typename T>
void acceder(BTNode<T>* p){
    cout<<p->value<<" ";
}

template <typename T>
void preOrden(BTNode<T>* p){
    if(p==nullptr) return;
    acceder(p);
    preOrden(p->leftChild);
    preOrden(p->rightChild);
}

template <typename T>
void inOrden(BTNode<T>* p){
    if(p==nullptr) return;
    acceder(p);
    inOrden(p->leftChild);
    inOrden(p->rightChild);
}

template <typename T>
void postOrden(BTNode<T>* p){
    if(p==nullptr) return;
    acceder(p);
    postOrden(p->leftChild);
    postOrden(p->rightChild);
}

template <typename T>
void anchura(BTNode<T>* p){
    if(p==nullptr) return;
    DLList<BTNode<T>*> q;
    q.preInsert(q.first(), p);
    while(!q.isEmpty()){
        BTNode<T>* c=q.pop();
        acceder(c);
        if(c->leftChild!=nullptr){
            q.push(c->leftChild);
        } if(c->rightChild!=nullptr){
            q.push(c->rightChild);
        }
    }
}