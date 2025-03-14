#include <iostream>
#include "../Implementations/arboles.cpp"
using namespace std;

/*Usando las primitivas de árboles generales desarrolle una función 
que retorne la suma de todos los enteros comprendidos entre dos niveles.*/

int twoLevelSum(GTNode<int>* root, int level, int current=0, int sum=0){
    if(current==level+2) return sum;
    Node<GTNode<int>*>* p=root->children.first();
    if(!current<level){
        sum+=root->value;
    }
    while(p!=nullptr){
        sum=twoLevelSum(p->payload, level, current+1, sum);
        p->payload->children.next(p);
    }

    return sum;
}

int main(){
    GTree<int> tree(1);
    tree.addChildren(2, &(tree.root));
    tree.addChildren(3, &(tree.root));
    tree.addChildren(4, &(tree.root));

    cout<<twoLevelSum(&tree.root,1)<<endl;

    return 0;
}