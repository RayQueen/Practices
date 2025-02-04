#include <iostream>
using namespace std;

/*Para  las  siguientes  instrucciones,  haga  un  mapa  de  memoria  que  
muestre  que  ocurre  en  ella,  y  cuál  es  la  salida  del programa.*/

struct node { 
   int info; 
   node *next; 
};

int main ( ) { 
    node *p, *r, *s; //Se crean tres punteros a nodos, p, r y s
    p = new node(); 
    s = new node(); //Se le asignan a p, r y s un puntero para cada uno
    r = new node(); 
    p->next = r; //Se le asigna la direccion de r a puntero next del nodo al que p apunta
    r->next = s; //Se le asigna la direccion de s a puntero next del nodo al que r apunta
    s->next = p; //Se le asigna la direccion de p a puntero next del nodo al que s apunta
    s->info = 3; //Se le asigna el valor 3 al entero info del nodo al que s apunta
    p->next->next->next->info = 2; //Se le asigna el valor 2 al entero info del nodo al que p apunta
    s->next->next->info = 1; //Se le asigna el valor 1 al entero info del nodo al que r apunta
    p = s->next; //Se vuelve a asignar al puntero p la direccion del nodo al que ya apuntaba anteriormente
    std::cout << p->info << " " << s->info << " " << r->info << std::endl;  //Se imprime "2 3 1"
    return 0; 
}