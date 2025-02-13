#include <iostream>
#include "Stack.cpp"
using namespace std;

/*Utilizando únicamente las primitivas de la clase Pila, se quiere que Ud. 
desarrolle un procedimiento que dada una pila P, la invierta. 
No debe utilizar estructuras auxiliares.*/

template <typename T>
void invertir(Stack<T> &P) {
    if (!P.isEmpty()) {
        T x = P.pop();
        invertir(P);
        apilarEnFondo(P,x);
    }
}

template <typename T>
void apilarEnFondo(Stack<T> &P, const T& elemento) {
    if (P.isEmpty()) {
        P.push(elemento);
    } else {
        T cima = P.pop();
        apilarEnFondo(P,elemento);
        P.push(cima);
    }
}

int main(){
    Stack<int> A,B;

    A.push(1);
    A.push(2);
    A.push(3);
    A.push(4);
    A.push(5);
    A.push(6);

    A.printStack();

    invertir(A);

    A.printStack();

    return 0;
}