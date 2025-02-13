#include <iostream>
#include "Stack.cpp"
using namespace std;

/* Dados  dos  enteros  positivos,  cuyos  dígitos  están  almacenados  en  una  
pila,  elabore  un  algoritmo,  utilizando  las primitivas del tipo PILA, que 
realice la suma de estos números dejando el resultado en otra pila. 
Ejemplo: 145 + 535 = 680*/

void stackSum(Stack<int> &A, Stack<int> &B, Stack<int> &C){
    int x= (A.pop());
    int y= (B.pop());
    C.push(x+y);
}

int main(){
    Stack<int> A,B,C;

    A.push(145);
    B.push(535);

    A.printStack();
    B.printStack();
    C.printStack();

    stackSum(A,B,C);

    C.printStack();

    return 0;
}
