#include <iostream>
#include "SimpleLinkedList.cpp"
using namespace std;

/*Dada una lista  enlazada  simple,  implemente  la  operación  palíndrome, la 
cual verifica  si una  secuencia  de caracteres almacenada  en  la  lista  es  
palíndrome  o  no.  Una  secuencia  de  caracteres  es  palíndrome  si  el  
resultado  de  leerla  de izquierda a derecha, es igual al resultado de leerla 
de derecha a izquierda.*/

bool palindrome(SLList<char> &list, Node<char>*li, Node<char>*ls){
    if(li->payload!=ls->payload)return false;
    if(list.findPrev(li)==ls||li==ls) return true;
    list.next(li);
    return palindrome(list, li, list.findPrev(ls));
}

bool palindrome(SLList<char> &list){
    return palindrome(list, list.first(), list.findPrev(list.last()));
}

int main(){
    SLList<char> A;

    A.insert(A.first(), 'a');
    A.insert(A.first(), 'b');
    A.insert(A.first(), 'c');
    A.insert(A.first(), 'd');
    A.insert(A.first(), 'c');
    A.insert(A.first(), 'b');
    A.insert(A.first(), 'a');

    printList(A);
    cout<<endl;

    if(palindrome(A)){
        cout<<"Es palindrome."<<endl;
    }else{
        cout<<"No es palindrome."<<endl;
    }

    return 0;
}