#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    int* arr;
}Tree;
Tree* create_tree(int n){
    Tree* temp = (Tree*)malloc(sizeof(Tree));
    temp->arr = (int*)malloc(sizeof(int)*((int)pow(2,n) - 1));
    for (int i=0; i<(int)pow(2,n) - 1; i++){
        temp->arr[i] = -1;
    }
    return temp;
}
void insert_node(Tree* tree, int value){
    int index = 0;
    while (1){
        if (tree->arr[index] == -1){
            tree->arr[index] = value;
            break;
        }
        else if (tree->arr[index] > value){
            index = index*2+1;
        }
        else{
            index = index*2+2;
        }
    }
}

void inorder(Tree* tree, int index){
    if (tree->arr[index] != -1){
        inorder(tree, index*2+1);
        printf("%d ", tree->arr[index]);
        inorder(tree, index*2+2);
    }
}

int main(){
    Tree* tree = create_tree(4);
    insert_node(tree, 17);
    insert_node(tree, 12);
    insert_node(tree, 6);
    insert_node(tree, 15);
    insert_node(tree, 19);
    insert_node(tree, 18);
    insert_node(tree, 21);
    inorder(tree,0);
}
