#include <iostream>
using namespace std;

template <typename T>
class ListNode {
public:
	T payload;
	ListNode<T>* next;
	ListNode<T>* prev;

	ListNode(T payload) {
		this->payload = payload;
		prev = next = nullptr;
	}

	/*
	  * Sobrecarga del operador <<, por la definicion del operador, recibe dos parametros,
	  * el primero es el stream donde se agrega el texto que se escribe,
	  * el segundo es el objeto que se escribe.
	  *
	  * Ya que el operador trabaja sobre un parametro, si queremos acceder a los atributos privados del objeto necesitamos hacer que el operador sea friend de la clase,
	  * de lo contrario solo se podra utilizar los atributos y metodos publicos del objeto que se pasa por parametro
	*/
	friend ostream& operator<<(ostream& out, ListNode<T>& object) {
		out << "Payload: " << object.payload;

		out << " prev: ";
		if (object.prev != nullptr) out << object.prev->payload;
		else out << "null";

		out << " next: ";
		if (object.next != nullptr) out << object.next->payload;
		else out << "null";

		return out;
	}
};

template <typename T>
class List {
private:
	ListNode<T>* _first;
	ListNode<T>* _last;
	int x;
public:
	List() {
		_first = _last = nullptr;
		x = INT_MAX;
	}

	~List() {
		while (!isEmpty()) remove(first());
		_first = _last = nullptr;
	}

	void preInsert(T value, ListNode<T>* position) {
		ListNode<T>* newNode = new ListNode<T>(value);
		newNode->next = position;

		if (position != nullptr) {
			newNode->prev = position->prev;
			position->prev = newNode;
		}

		if (newNode->prev != nullptr) newNode->prev->next = newNode;

		if (isEmpty()) _first = _last = newNode;

		if (position == _first) _first = newNode;
	}

	void postInsert(T value, ListNode<T>* position) {
		ListNode<T>* newNode = new ListNode<T>(value);
		newNode->prev = position;

		if (position != nullptr) {
			newNode->next = position->next;
			position->next = newNode;
		}

		if (newNode->next != nullptr) newNode->next->prev = newNode;

		if (isEmpty()) _first = _last = newNode;

		if (position == _last) _last = newNode;
	}

	void remove(ListNode<T>* position) {
		if (position == nullptr) return;

		if (position == _first) _first = position->next;
		if (position == _last) _last = position->prev;

		if (position->prev != nullptr) position->prev->next = position->next;
		if (position->next != nullptr) position->next->prev = position->prev;

		delete position;
	}

	bool isEmpty() { return _first == nullptr; }

	ListNode<T>* first() { return _first; }

	ListNode<T>* last() { return _last; }

	/*
	* Sobrecarga del operador <<, por la definicion del operador, recibe dos parametros,
	* el primero es el stream donde se agrega el texto que se escribe,
	* el segundo es el objeto que se escribe.
	*
	* Ya que el operador trabaja sobre un parametro, si queremos acceder a los atributos privados del objeto necesitamos hacer que el operador sea friend de la clase,
	* de lo contrario solo se podra utilizar los atributos y metodos publicos del objeto que se pasa por parametro
	*/
	friend ostream& operator<<(ostream& out, List<T>& object) {
		if (object.isEmpty()) {
			out << "Empty";
			return out;
		}

		ListNode<T>* p = object.first();
		while (p != nullptr) {
			out << *p << " ";
			p = p->next;
		}

		return out;
	}
};

template <typename T>
class Queue {
private:
	// En vez de heredar simplmente manejo una lista interna y con ella simulo la Cola
	List<T> data;
public:
	void push(T value) {
		data.postInsert(value, data.last());
	}

	T pop() {
		T result = data.first()->payload;

		data.remove(data.first());

		return result;
	}

	bool isEmpty() {
		return data.isEmpty();
	}

	/*
	* Sobrecarga del operador <<, por la definicion del operador, recibe dos parametros,
	* el primero es el stream donde se agrega el texto que se escribe,
	* el segundo es el objeto que se escribe.
	*
	* Ya que el operador trabaja sobre un parametro, si queremos acceder a los atributos privados del objeto necesitamos hacer que el operador sea friend de la clase,
	* de lo contrario solo se podra utilizar los atributos y metodos publicos del objeto que se pasa por parametro
	*/
	friend ostream& operator<<(ostream& out, Queue<T>& object) {
		out << object.data;
		return out;
	}
};

template <typename T>
class AVLNode {
public:
	T payload; // Contenido del nodo
	AVLNode<T>* left; // Hijo izquierdo
	AVLNode<T>* right; // Hijo derecho
	unsigned int height; // Altura del arbol que tiene como raiz al nodo actual
	int count; // Cantidad de veces que el nodo se encuentra en el arbol, esto evita insertar duplicados

	AVLNode(T value) {
		payload = value;
		left = nullptr;
		right = nullptr;
		height = 1; // Suponemos que la altura de una arbol que no tiene hijos es 1
		count = 1;
	}

	// Calcula la altura del arbol izquierdo
	unsigned int leftChildHeight() {
		if (left == nullptr) return 0;
		return left->height;
	}

	// Calcula la altura del arbol derecho
	unsigned int rightChildHeight() {
		if (right == nullptr) return 0;
		return right->height;
	}

	// Calcula el balance del nodo
	int balance() {
		return leftChildHeight() - rightChildHeight();
	}

	// Indica si el nodo es una hoja
	bool isLeaf() {
		return left == nullptr && right == nullptr;
	}

};

template <typename T>
class AVL {
public:
	AVL() {
		root = nullptr;
	}
	~AVL() {
		destroyTree(root);
		root = nullptr;
	}

	void insert(T value) {
		insert(value, root);
	}

	void deleteValue(T value) {
		deleteNode(value, root);
	}

	AVLNode<T>* getRoot() const {
		return root;
	}

	bool hasValue(T value) {
		return findNode(value, root) != nullptr;
	}

private:
	// Raiz del arbol
	AVLNode<T>* root;

	/*
	* Busca el nodo cuyo valor coincida con el suministrado, retorna la referencia al nodo
	*/
	AVLNode<T>*& findNode(T value, AVLNode<T>* &root) {
		if (root == nullptr) return root;

		if (value == root->payload) return root;

		if (value < root->payload) return findNode(value, root->left);

		return findNode(value, root->right);
	}

	/*
	* Busca el nodo mas pequenio del arbol, el que tenga un value mas pequenio
	*/
	AVLNode<T>*& findMinValueNode(AVLNode<T>* node) {
		if (node == nullptr) return node;
		
		while (node->left != nullptr)
			node = node->left;

		return node;

	}
	void insert(T value, AVLNode<T>* &root) {
		// Caso base, alcanzamos una hoja y se puede detener la insercion
		if (root == nullptr) {
			root = new AVLNode<T>(value);
			return;
		}

		// Si es un duplicado incremento el contador y me detengo
		if (value == root->payload) {
			root->count++;
			return;
		}

		// Inserto el valor en la rama correspondiente manteniendo las condiciones de un ABB
		if (value < root->payload) {
			insert(value, root->left);
		}
		else {
			insert(value, root->right);
		}

		// Se balancea el nodo, de ser necesario
		rebalanceNode(root);

		// Finalmente se actualiza la altura del nodo actual
		root->height = computeHeight(root);
	}
	
	/*
	* Busca el nodo cuyo valor coincida y luego lo borra
	*/
	void deleteNode(T value, AVLNode<T>* &root) {
		if (root == nullptr) return;

		// Primero busco el nodo
		if (value < root->payload) deleteNode(value, root->left);
		else if (value > root->payload) deleteNode(value, root->right);
		else {
			// Si tiene duplicados solo actualizo el contador y termino
			if (root->count > 1) {
				root->count--;
				return;
			}

			// De no ser asi evaluo que tipo de nodo es

			// No tiene hijos o solo tiene uno, puedo borrarlo y sustir el valor del puntero que lo contenia por el del hijo
			if (root->left == nullptr || root->right == nullptr) {
				AVLNode<T>* child = root->left != nullptr ? root->left : root->right;
				delete root;
				root = child;
			}
			else { // Tiene ambos hijos
				// Busco el hijo mas pequenio de la rama derecha
				AVLNode<T>*& smallerChild = findMinValueNode(root->right);
				// Actualizo el nodo actual con la informaci�n del valor m�s peque�o de la rama derecha
				root->payload = smallerChild->payload;
				// Se borra el nodo mas pequenio del arbol 
				deleteNode(smallerChild->payload, root->right);
			}

		}

		// El nodo pudo haber sido remplazado por nulo si era una hoja, por tanto su valor seria nulo
		if (root == nullptr) return;

		// Se rebalancea el punto donde se elimino el nodo
		rebalanceNode(root);

		// Finalmente se actualiza la altura del nodo actual
		root->height = computeHeight(root);
	}

	/*
	* Verifica si el nodo suministrado esta desbalanceado y en caso de ser asi
	* aplica las rotaciones necesarias, el puntero a nodo se pasa por referencia para poder alterar su valor con las rotaciones
	*/
	void rebalanceNode(AVLNode<T>* &root) {
		if (root == nullptr) return;

		// Se obtiene el balance del nodo para verificar si hay que hacer una rotacion
		int actualBalance = root->balance();
		
		// Rama izquierda esta desbalanceada
		if (actualBalance > 1) {
			int childBalance = root->left->balance();
			
			// Caso izquierda, derecha. Rama cruzada, debemos estirar la rama.
			if (childBalance < 0) {
				// Para esto aplicamos una rotaci�n a la izquierda en el hijo de la izquierda
				leftRotation(root->left);
			}

			// Siempre caeremos en el Caso izquierda, izquierda. Rama estirada, debemos mover la raiz hacia la derecha (rotar a la derecha)
			rightRotation(root);
		}
		// Rama derecha esta desbalanceada
		else if (actualBalance < -1) {
			int childBalance = root->right->balance();

			// Caso derecha, izquierda. Rama cruzada, debemos estirar la rama.
			if (childBalance > 0) {
				// Para esto aplicamos una rotaci�n a la derecha en el hijo de la derecha
				rightRotation(root->right);
			}

			// Siempre caeremos en el Caso derecha, derecha. Rama estirada, debemos mover la raiz hacia la izquierda (rotar a la izquierda)
			leftRotation(root);
		}
	}

	/*
	* Aplica una rotacion a la derecha, eso implica que el hijo izquierdo pasa a ser la raiz y la raiz el hijo derecho
	*/
	void rightRotation(AVLNode<T>* &root) {
		if (root == nullptr) return;

		AVLNode<T>* currentLeft = root->left;
		AVLNode<T>* rightChildOfCurrentLeft = currentLeft->right;

		// Como el hijo izquierdo sera la nueva raiz, el nodo que es actualmente la raiz deberia estar a la derecha, por lo que pasa a ser su hijo derecho
		currentLeft->right = root;
		// Los hijos que estaban a la derecha de la nueva raiz, son menores que los de la raiz actual, por lo que deberian ser su hijo izquierdo
		root->left = rightChildOfCurrentLeft;

		// Luego de aplicar las rotaciones es necesario actualizar la altura de los nodos que se movieron
		root->height = computeHeight(root);
		currentLeft->height = computeHeight(currentLeft);

		// Finalmente modificamos la raiz
		root = currentLeft;
	}

	/*
	* Aplica una rotacion a la izquierda, eso implica que el hijo derecho pasa a ser la raiz y la raiz el hijo izquierdo
	*/
	void leftRotation(AVLNode<T>*& root) {
		if (root == nullptr) return;

		AVLNode<T>* currentRight = root->right;
		AVLNode<T>* leftChildOfCurrentRight = currentRight->left;

		// Como el hijo derecho sera la nueva raiz, el nodo que es actualmente la raiz deberia estar a la izquierda, por lo que pasa a ser su hijo izquierdo
		currentRight->left = root;
		// Los hijos que estaban a la izquierda de la nueva raiz, son mayores que los de la raiz actual, por lo que deberian ser su hijo derecho
		root->right = leftChildOfCurrentRight;

		// Luego de aplicar las rotaciones es necesario actualizar la altura de los nodos que se movieron
		root->height = computeHeight(root);
		currentRight->height = computeHeight(currentRight);

		// Finalmente modificamos la raiz
		root = currentRight;
	}

	/*
	* Calcula la altura del nodo indicado
	*/
	unsigned int computeHeight(AVLNode<T>* node) {
		if (node == nullptr) return 0;

		return max(node->leftChildHeight(), node->rightChildHeight()) + 1;
	}

	/*
	* Borra recursivamente todos los nodos haciendo un recorrido post-orden sobre el arbol
	*/
	void destroyTree(AVLNode<T>* root) {
		if (root == nullptr) return;

		// Borro la rama izquierda
		if (root->left != nullptr) destroyTree(root->left);
		// Borro la rama derecha
		if (root->right != nullptr) destroyTree(root->right);
		delete root;
	}
};

// Realiza un recorrido por anchura e imprime los valores del arbol

template <typename T>
void printTree(const AVL<T> &avl) {
	Queue<AVLNode<T>*> queue;
	queue.push(avl.getRoot());

	while (!queue.isEmpty()) {
		AVLNode<T>* node = queue.pop();
		if (node->left != nullptr) queue.push(node->left);
		if (node->right != nullptr) queue.push(node->right);

		cout << node->payload << " ";
	}
}

int main() {
	AVL<int> avl;

	int valueToSearch1 = 6;
	int valueToSearch2 = 40;
	int values[] = { 1,2,4,5,6,-10,-20,30 };

	int size = sizeof(values) / sizeof(int);

	for (int i = 0; i < size; i++) {
		cout << "Insert " << values[i] << endl;
		avl.insert(values[i]);
		printTree(avl);
		cout << endl << endl;
	}

	cout << "Has value " << valueToSearch1 << ": " << (avl.hasValue(valueToSearch1) ? "True" : "False") << endl;
	cout << "Has value " << valueToSearch2 << ": " << (avl.hasValue(valueToSearch2) ? "True" : "False") << endl;
	
	cout << "Delete " << 2 << endl;
	avl.deleteValue(2);
	printTree(avl);
	cout << endl << endl;

	cout << "Delete " << 60 << endl;
	avl.deleteValue(60);
	printTree(avl);
	cout << endl << endl;

	cout << "Delete " << -10 << endl;
	avl.deleteValue(-10);
	printTree(avl);
	cout << endl << endl;

	cout << "Delete " << 30 << endl;
	avl.deleteValue(30);
	printTree(avl);
	cout << endl << endl;

	cout << "Delete " << 1 << endl;
	avl.deleteValue(1);
	printTree(avl);
	cout << endl << endl;

	cout << "Delete " << -20 << endl;
	avl.deleteValue(-20);
	printTree(avl);
	cout << endl << endl;
	
	return 0;
}