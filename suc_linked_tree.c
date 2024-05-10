#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* SucNode;
}treeNode;

typedef struct BinaryTree{
    treeNode*  root;
}BinaryTree;

treeNode* create_tree_node(int data){
    treeNode* new_node = (treeNode*)malloc(sizeof(treeNode));
    if (new_node == NULL){
        printf("memory allocation failed");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->SucNode = NULL;
    return new_node;
}

treeNode* insert_node(treeNode* root, int data){
    if (root == NULL){
        return create_tree_node(data);
    }
    if (data < root->data){
        root->left = insert_node(root->left, data);
    } 
    if (data >root->data){
        root->right = insert_node(root->right, data);
    }
     
    return root;
}