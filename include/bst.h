#ifndef BST_H
#define BST_H

#include "types.h"

typedef struct BSTNode {
    Paket data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *insertBST(BSTNode *root, Paket p);
BSTNode *searchBST(BSTNode *root, int id);
BSTNode *deleteBST(BSTNode *root, int id);
void preorderBST(const BSTNode *root);
void inorderBST(const BSTNode *root);
void postorderBST(const BSTNode *root);
void freeBST(BSTNode *root);

#endif
