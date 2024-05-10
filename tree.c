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
        printf("%d ",root->data);
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


treeNode* delete_leaf_node(treeNode* root, int value){
    if (root != NULL){
        if (root->data == value)
            return NULL;
        root->left = delete_leaf_node(root->left, value);
        root->right = delete_leaf_node(root->right, value);
    }
    return root;
}

treeNode* findmin(treeNode* root){
    while (root->left != NULL){
        root = root->left;
    }
    return root;
}

treeNode* delete_node(treeNode* root, int val){
    if(root == NULL){
       return NULL;
    }
    if(val == root->data){
        if(root->left == NULL){
            treeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if(root->right == NULL){
            treeNode* temp = root->left;
            free(root);
            return temp;
        }
        treeNode* temp = findmin(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);

    }
    else if(val < root->data){
        root->left = delete_node(root->left, val);
    }
    else{
        root->right = delete_node(root->right, val);
    }
}

treeNode* get_node_sibling(treeNode* root, int key){
    if (root == NULL){
        return NULL;
    }
    if (root->left != NULL){
        if (root->left->data == key){
            return root->right;
        }
    }
    if (root->right != NULL){
        if (root->right->data == key){
            return root->left;
        }
    }
    treeNode* temp = get_node_sibling(root->left, key);
    if (temp){
        return temp;
    }
    temp = get_node_sibling(root->right, key);
    return temp;
}
int get_node_depth(treeNode* root, int key){
    if (root == NULL){
        return -1;
    }
    if (root->data == key){
        return 0;
    }else if (root->data> key)
    {   
        int n = get_node_depth(root->left, key);
        if (n == -1){
            return -1;
        }
        return 1 + n;
    }else{
        int n = get_node_depth(root->right, key);
        if (n == -1){
            return -1;
        }
        return 1 + n;
    }

}
int level(treeNode* root, int key){
    return 1 + get_node_depth(root, key);
}
int get_height(treeNode* root){
    if (root == NULL){
        return -1;
    }
    int h1 = get_height(root->left);
    int h2 = get_height(root->right);
    if (h1 > h2){
        return h1 + 1;
    }else{
        return h2 + 1;
    }
}
int main(){
    BinaryTree Tree;
    Tree.root = NULL;
    Tree.root = insert_node(Tree.root, 17);
    Tree.root = insert_node(Tree.root, 15);
    Tree.root = insert_node(Tree.root, 11);
    Tree.root = insert_node(Tree.root, 21);
    Tree.root = insert_node(Tree.root, 16);
    Tree.root = insert_node(Tree.root, 18);
    Tree.root = insert_node(Tree.root, 23);
    Tree.root = insert_node(Tree.root, 89);
    
    /*
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
    */
    printf("before deletion inorder\n");
    inorder(Tree.root);
    printf("\n");
    delete_node(Tree.root, 16);
    printf("after deletion inorder\n");
    inorder(Tree.root);
    printf("\n");
    treeNode* sibling = get_node_sibling(Tree.root, 16);

    sibling ? printf("sibling: of 16 is %d\n", sibling->data) : printf("sibling: of 16 is NULL\n");
    printf("height %d\n", get_height(Tree.root));
    printf("depth %d", get_node_depth(Tree.root, 17));
    return 0;   
}