#include <stdio.h>
#include <stdlib.h>
//write ierative recurcive version of code for preorder postorder and inorder
#define MAX_SIZE 100
typedef struct treeNode{
    int data;
    struct treeNode* left;
    struct treeNode* right;
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




typedef struct{
    treeNode* items[MAX_SIZE];
    int top;
}Stack;
Stack* create_stack(){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed.\n");
        exit(-1);
    }
    stack->top = -1;
    return stack;
}
int is_empty(Stack* stack){
    return stack->top == -1;
}

int is_full(Stack* stack){
    return stack->top==MAX_SIZE-1;
}
void  push(Stack* stack, treeNode* item){
    if (is_full(stack)){
        printf("Stack is Full, Cannot push %d. \n",item);
    }else{
        stack->items[++stack->top]=item;
    }
}
treeNode* pop(Stack* stack){
    if (is_empty(stack)){
        printf("Stack is empty, Cannot pop, \n");
        return NULL;
    }
    return stack->items[stack->top--];

}
int get_size(Stack* stack){
    return stack->top+1;
}
treeNode* peek(Stack* stack){
    if (is_empty(stack)){
        printf("Stack is empty, Cannot peek, \n");
        return NULL;
    }
    return stack->items[stack->top];

}
void destroy_stack(Stack* stack){
    free(stack);
}





treeNode* inorder(treeNode* root){
    if (root != NULL){
        inorder(root->left);
        printf("%d\n",root->data);
        inorder(root->right);
    }
    return NULL;
}
treeNode* clone_by_preorder(treeNode* root){
    
    if (root != NULL){
        treeNode* clone = create_tree_node(root->data);
        clone->left = clone_by_preorder(root->left);
        clone->right = clone_by_preorder(root->right);
        return clone;
    }
    return NULL;
}
treeNode* del_by_postorder(treeNode* root){
    if (root != NULL){
        root->left = del_by_postorder(root->left);
        root->right = del_by_postorder(root->right);
        free(root);
        root = NULL;
    }
    return root;
}


void inorderIerative(treeNode* root){
        Stack* stack = create_stack();
    treeNode* current = root;

    while (current != NULL || !is_empty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = pop(stack);
        printf("%d \n", current->data);
        current = current->right;
    }
    destroy_stack(stack);
}


void preorderIerative(treeNode* root){
    if (root == NULL){
        return;
    }
    Stack* stack = create_stack();
    treeNode* current;
    push(stack, root);
    while (!is_empty(stack)){
        current = pop(stack);
        printf("%d \n",current->data);
        if (current->right != NULL) push(stack, current->right);
        if (current->left != NULL) push(stack, current->left);
    }
    destroy_stack(stack);
}
void postorderIerative(treeNode* root){
    if (root == NULL)
        return;

    Stack* stack = create_stack();
    treeNode* current = root;
    treeNode* lastVisited = NULL;

    while (current != NULL || !is_empty(stack)) {
        while (current != NULL) {
            push(stack, current);
            current = current->left;
        }
        current = peek(stack);
        if (current->right != NULL && current->right != lastVisited) {
            current = current->right;
        } else {
            current = pop(stack);
            printf("%d \n", current->data);
            lastVisited = current;
            current = NULL;
        }
    }
    destroy_stack(stack);
}





int main(){
    BinaryTree Tree;
    Tree.root = NULL;
    Tree.root = insert_node(Tree.root, 6);
    Tree.root = insert_node(Tree.root, 2);
    Tree.root = insert_node(Tree.root, 5);
    Tree.root = insert_node(Tree.root, 3);
    Tree.root = insert_node(Tree.root, 4);
    Tree.root = insert_node(Tree.root, 7);
    Tree.root = insert_node(Tree.root, 1);
    printf("clone by preorder\n");
    BinaryTree clone;
    clone.root = clone_by_preorder(Tree.root);
    printf("inorder order traversal of clone\n");
    inorder(clone.root);
    printf("delting clone by postorder\n");
    del_by_postorder(clone.root);
    printf("inorder traversal ierative\n");
    inorderIerative(Tree.root);
    printf("inorder traversal ierative\n");
    preorderIerative(Tree.root);
    printf("inorder traversal ierative\n");
    postorderIerative(Tree.root);

    return 0;   
}