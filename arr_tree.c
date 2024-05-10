#include <stdio.h>
#include <stdlib.h>


typedef struct Tree{
    int* arr;
}Tree;
Tree* create(int n){
    Tree* temp = (Tree*)malloc(sizeof(Tree));
    temp->arr = (int*)malloc(sizeof(int)*(2^n - 1));
    for (int i=0; i<2^n - 1; i++){
        temp->arr[i] = -1;
    }
    return temp;
}
void insert_node(Tree* tree, int value,int start){
    if (tree->arr[start] != -1){
        tree->arr[start] = value;
        return;
    }
    if (tree->arr[start] < value){
        insert_node(tree, value, start*2+1);
    }
    if (tree->arr[start] >= value){
        insert_node(tree, value, start*2+2);
    }
    

}
int main(){
    Tree* tree = create(3);
    insert_node(tree, 10, 0);
    insert_node(tree, 10, 0);
    insert_node(tree, 10, 0);
    insert_node(tree, 10, 0);
    insert_node(tree, 10, 0);
    int x=0;
    while (tree->arr != NULL){
        printf("%d ",tree->arr[x]);
    }
    
}
