#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode* left;
    struct treeNode* right;
    struct treeNode* sucNode;
} treeNode;

typedef struct BinaryTree {
    treeNode* root;
} BinaryTree;

treeNode* create_tree_node(int data) {
    treeNode* new_node = (treeNode*)malloc(sizeof(treeNode));
    if (new_node == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->sucNode = NULL;
    return new_node;
}

treeNode* insert_node(treeNode* root, int data, treeNode* prev) {
    if (root == NULL) {
        treeNode* new_node = create_tree_node(data);  
        return new_node;
    }

    if (data < root->data) {
        if (root->left != NULL){
            root->left = insert_node(root->left, data, prev);
        }else{
            root->left = create_tree_node(data);
            root->left->sucNode = root;
        }
    } else if (data >= root->data) {
        if (root->right != NULL){
            root->right = insert_node(root->right, data, prev);
        }else{
            root->right = create_tree_node(data);
            root->right->sucNode = root->sucNode;
            root->sucNode = root->right;
        }
    }

    return root;
}

BinaryTree* create_binary_tree() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    tree->root = NULL;
    return tree;
}

void insert(BinaryTree* tree, int data) {
    tree->root = insert_node(tree->root, data, NULL);
}

void inorder(treeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        if (root->sucNode == NULL) {
            printf("data:%d, successor data: NULL\n", root->data);
        } else {
            printf("data:%d, successor data: %d\n", root->data, root->sucNode->data);
        }
        inorder(root->right);
    }
}

int main() {
    BinaryTree* tree = create_binary_tree();

    insert(tree, 6);
    insert(tree, 3);
    insert(tree, 9);
    insert(tree, 2);
    insert(tree, 8);
    insert(tree, 11);
    insert(tree, 4);
    insert(tree, 5);

    inorder(tree->root);

    return 0;
}
