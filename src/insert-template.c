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
ceBtree_Status INSERT_FUNC_NAME (
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
            
            #ifdef CLEANUP_FUNC_NAME
                CLEANUP_FUNC_NAME (tree, cur->left);
            #endif
            
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
            
            #ifdef CLEANUP_FUNC_NAME
                CLEANUP_FUNC_NAME (tree, cur->right);
            #endif
            
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
