#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

BSTNode *insertBST(BSTNode *root, Paket p) {
    if (!root) {
        BSTNode *node = (BSTNode *)malloc(sizeof(BSTNode));
        node->data = p;
        node->left = node->right = NULL;
        return node;
    }
    if (p.id < root->data.id) root->left = insertBST(root->left, p);
    else if (p.id > root->data.id) root->right = insertBST(root->right, p);
    return root;
}

BSTNode *searchBST(BSTNode *root, int id) {
    if (!root || root->data.id == id) return root;
    if (id < root->data.id) return searchBST(root->left, id);
    return searchBST(root->right, id);
}

static BSTNode *findMin(BSTNode *node) {
    while (node && node->left) node = node->left;
    return node;
}

BSTNode *deleteBST(BSTNode *root, int id) {
    BSTNode *temp;
    if (!root) return NULL;
    if (id < root->data.id) {
        root->left = deleteBST(root->left, id);
    } else if (id > root->data.id) {
        root->right = deleteBST(root->right, id);
    } else {
        if (!root->left) {
            temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            temp = root->left;
            free(root);
            return temp;
        }
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteBST(root->right, temp->data.id);
    }
    return root;
}

void preorderBST(const BSTNode *root) {
    if (!root) return;
    printf("[ID:%d | %s] ", root->data.id, root->data.resi);
    preorderBST(root->left);
    preorderBST(root->right);
}

void inorderBST(const BSTNode *root) {
    if (!root) return;
    inorderBST(root->left);
    printf("[ID:%d | %s] ", root->data.id, root->data.resi);
    inorderBST(root->right);
}

void postorderBST(const BSTNode *root) {
    if (!root) return;
    postorderBST(root->left);
    postorderBST(root->right);
    printf("[ID:%d | %s] ", root->data.id, root->data.resi);
}

void freeBST(BSTNode *root) {
    if (!root) return;
    freeBST(root->left);
    freeBST(root->right);
    free(root);
}
