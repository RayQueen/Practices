#include <iostream>
using namespace std;

/*Para  las  siguientes  instrucciones,  haga  un  mapa  de  memoria  que  
muestre  que  ocurre  en  ella,  y  cuál  es  la  salida  del programa.*/

struct node { 
   int info; 
   node *next; 
};

int main ( ) { 
    node *p, *r, *s; 
    p = new node(); 
    s = new node(); 
    r = new node(); 
    p->next = r; 
    r->next = s; 
    s->next = p; 
    s->info = 3; 
    p->next->next->next->info = 2; 
    s->next->next->info = 1; 
    p = s->next; 
    std::cout << p->info << " " << s->info << " " << r->info << std::endl; 
    return 0; 
}