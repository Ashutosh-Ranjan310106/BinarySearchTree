#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Tree{
    int* arr;
}Tree;
Tree* create(int n){
    Tree* temp = (Tree*)malloc(sizeof(Tree));
    temp->arr = (int*)malloc(sizeof(int)*(pow(2,n) - 1));
    for (int i=0; i<pow(2,n) - 1; i++){
        temp->arr[i] = -1;
    }
    return temp;
}
void insert_node(Tree* tree, int value){
    int start = 0;
    while (1){
        if (tree->arr[start] == -1){
            tree->arr[start] = value;
            break;
        }
        else if (tree->arr[start] < value){
            start = start*2+1;
        }
        else if (tree->arr[start] >= value){
            start = start*2+2;
        }
    }
    

}
int main(){
    printf("asd%d",pow(2,3));
    Tree* tree = create(3);
    printf("ad");
    insert_node(tree, 234);
    insert_node(tree, 14);
    insert_node(tree, 23);
    insert_node(tree, 112);
    insert_node(tree, 123);
    printf("a23d");
    int x=0;
    while (x < 10){
        printf("a23d\n");
        printf("<%d,%d>",tree->arr[x], x);
        x++;
    }
    
}
