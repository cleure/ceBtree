#include "btree.h"
#include "helpers.h"
#include <stdlib.h>


/**
* Insert item into tree.
*
* @param    ceBtree *tree
* @param    void *key
* @param    void *data
* @param    int replace
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_Insert(
        ceBtree *tree,
        void *key, void *data,
        int replace) {
    
    // Allocate root node?
    if (tree->root == NULL) {
        tree->root = (ceBtreeNode *)
            malloc(sizeof(ceBtreeNode));
        
        // Handle OOM
        if (tree->root == NULL) {
            return CE_BTREE_STATUS_ERR;
        }
        
        // Initialize new node, using macro
        ceBtreeNodeInit(tree->root, key, data);
        tree->root->parent = NULL;
        
        return CE_BTREE_STATUS_OK;
    }
    
    ceBtree_Compare res;
    ceBtreeNode *cur = tree->root;
    
    while (1) {
        // Compare keys
        res = tree->cmpfn(cur->key, key);
        
        // if a > b
        if (res == CE_BTREE_COMPARE_GT) {
            if (cur->left != NULL) {
                // Recurse further down the tree
                cur = cur->left;
                continue;
            }
            
            // Allocate
            cur->left = (ceBtreeNode *)
                malloc(sizeof(ceBtreeNode));
            
            // Handle OOM
            if (cur->left == NULL) {
                return CE_BTREE_STATUS_ERR;
            }
            
            // Initialize new node, using macro
            ceBtreeNodeInit(cur->left, key, data);
            cur->left->parent = cur;
            
            return CE_BTREE_STATUS_OK;
        }
        
        // if a < b
        if (res == CE_BTREE_COMPARE_LT) {
            if (cur->right != NULL) {
                // Recurse further down the tree
                cur = cur->right;
                
                continue;
            }
            
            // Allocate
            cur->right = (ceBtreeNode *)
                malloc(sizeof(ceBtreeNode));
            
            // Handle OOM
            if (cur->right == NULL) {
                return CE_BTREE_STATUS_ERR;
            }
            
            // Initialize new node, using macro
            ceBtreeNodeInit(cur->right, key, data);
            cur->right->parent = cur;
            
            return CE_BTREE_STATUS_OK;
        }
        
        // if a == b
        if (res == CE_BTREE_COMPARE_EQ) {
            // Replace existing???
            if (replace == 1) {
                if (tree->freefn != NULL) {
                    tree->freefn(cur);
                }
                
                cur->key = key;
                cur->data = data;
            }
            
            return CE_BTREE_STATUS_OK;
        }
        
        // Oops, error... Return
        if (res == CE_BTREE_COMPARE_ERR) {
            return CE_BTREE_STATUS_ERR;
        }
    }
    
    return CE_BTREE_STATUS_ERR;
}

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

/**
* Perform Insert on Red Black Tree
*
* @param    ceBtree *tree
* @param    void *key
* @param    void *data
* @param    int replace
* @return   ceBtree_Status
**/
ceBtree_Status ceRBtree_Insert(
        ceBtree *tree,
        void *key, void *data,
        int replace) {
    
    // Allocate root node?
    if (tree->root == NULL) {
        tree->root = (ceBtreeNode *)
            malloc(sizeof(ceBtreeNode));
        
        // Handle OOM
        if (tree->root == NULL) {
            return CE_BTREE_STATUS_ERR;
        }
        
        // Initialize new node, using macro
        ceBtreeNodeInit(tree->root, key, data);
        tree->root->parent = NULL;
        tree->root->color = CE_BTREE_COLOR_BLACK;
        
        return CE_BTREE_STATUS_OK;
    }
    
    ceBtree_Compare res;
    ceBtreeNode *cur = tree->root;
    
    while (1) {
        // Compare keys
        res = tree->cmpfn(cur->key, key);
        
        // if a > b
        if (res == CE_BTREE_COMPARE_GT) {
            if (cur->left != NULL) {
                // Recurse further down the tree
                cur = cur->left;
                continue;
            }
            
            // Allocate
            cur->left = (ceBtreeNode *)
                malloc(sizeof(ceBtreeNode));
            
            // Handle OOM
            if (cur->left == NULL) {
                return CE_BTREE_STATUS_ERR;
            }
            
            // Initialize new node, using macro
            ceBtreeNodeInit(cur->left, key, data);
            cur->left->parent = cur;
            
            // Cleanup
            ceRBtree_InsertCleanup(tree, cur->left);
            
            return CE_BTREE_STATUS_OK;
        }
        
        // if a < b
        if (res == CE_BTREE_COMPARE_LT) {
            if (cur->right != NULL) {
                // Recurse further down the tree
                cur = cur->right;
                
                continue;
            }
            
            // Allocate
            cur->right = (ceBtreeNode *)
                malloc(sizeof(ceBtreeNode));
            
            // Handle OOM
            if (cur->right == NULL) {
                return CE_BTREE_STATUS_ERR;
            }
            
            // Initialize new node, using macro
            ceBtreeNodeInit(cur->right, key, data);
            cur->right->parent = cur;
            
            // Cleanup
            ceRBtree_InsertCleanup(tree, cur->right);
            
            return CE_BTREE_STATUS_OK;
        }
        
        // if a == b
        if (res == CE_BTREE_COMPARE_EQ) {
            // Replace existing???
            if (replace == 1) {
                if (tree->freefn != NULL) {
                    tree->freefn(cur);
                }
                
                cur->key = key;
                cur->data = data;
            }
            
            return CE_BTREE_STATUS_OK;
        }
        
        // Oops, error... Return
        if (res == CE_BTREE_COMPARE_ERR) {
            return CE_BTREE_STATUS_ERR;
        }
    }
    
    return CE_BTREE_STATUS_ERR;
}
