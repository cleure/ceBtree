#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

/**
* Red Black Tree Insert Cleanup. Called after a normal Binary Tree insert
* has been performed on the tree.
*
* @param    ceBtree *tree
* @param    ceBtreeNode *x
* @return   void
**/
static void ceRBtree_InsertCleanup(
        ceBtree *tree,
        ceBtreeNode *x) {
    
    ceBtreeNode *parent, *grandparent, *uncle;
    uint8_t uncle_color;
    
    // Set color to red
    x->color = CE_BTREE_COLOR_RED;
    
    // Loop to root
    while (x->parent != NULL && x->parent->color == CE_BTREE_COLOR_RED) {
        parent = x->parent;
        grandparent = parent->parent;
        
        if (parent == grandparent->left) {
            uncle = grandparent->right;
            if (uncle == NULL || uncle->color == CE_BTREE_COLOR_BLACK) {
                uncle_color = CE_BTREE_COLOR_BLACK;
            } else {
                uncle_color = CE_BTREE_COLOR_RED;
            }
            
            if (uncle_color == CE_BTREE_COLOR_RED) {
                uncle->color = CE_BTREE_COLOR_BLACK;
                parent->color = CE_BTREE_COLOR_BLACK;
                grandparent->color = CE_BTREE_COLOR_RED;
                x = grandparent;
                continue;
            }
            
            if (x == parent->right) {
                ceBtree_RotateLeft(tree, parent);
                
                ceBtreeNode *tmp;
                tmp = parent;
                parent = x;
                x = tmp;
            }
            
            parent->color = CE_BTREE_COLOR_BLACK;
            grandparent->color = CE_BTREE_COLOR_RED;
            ceBtree_RotateRight(tree, grandparent);
        } else {
            uncle = grandparent->left;
            
            if (uncle == NULL || uncle->color == CE_BTREE_COLOR_BLACK) {
                uncle_color = CE_BTREE_COLOR_BLACK;
            } else {
                uncle_color = CE_BTREE_COLOR_RED;
            }
            
            if (uncle_color == CE_BTREE_COLOR_RED) {
                uncle->color = CE_BTREE_COLOR_BLACK;
                parent->color = CE_BTREE_COLOR_BLACK;
                grandparent->color = CE_BTREE_COLOR_RED;
                x = grandparent;
                continue;
            }
            
            if (x == parent->left) {
                ceBtree_RotateRight(tree, parent);
                
                ceBtreeNode *tmp;
                tmp = parent;
                parent = x;
                x = tmp;
            }
            
            parent->color = CE_BTREE_COLOR_BLACK;
            grandparent->color = CE_BTREE_COLOR_RED;
            ceBtree_RotateLeft(tree, grandparent);
        }
    }
    
    tree->root->color = CE_BTREE_COLOR_BLACK;
}

#define INSERT_FUNC_NAME ceBtree_Insert
#include "insert-template.c"
#undef INSERT_FUNC_NAME

#define INSERT_FUNC_NAME ceRBtree_Insert
#define CLEANUP_FUNC_NAME ceRBtree_InsertCleanup
#include "insert-template.c"
#undef INSERT_FUNC_NAME
#undef CLEANUP_FUNC_NAME
