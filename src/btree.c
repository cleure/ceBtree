#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

/*

TODO:
    - Implement as Red/Black tree, when flag set

How to implement red/black trees:
    - insert.c could be macro-tized, for both binary tree and
      red black trees. Function pointers on the tree struct would
      point to the correct insert function.
    - Insert function could use if/else statements...

*/

/**
* Initialize a new btree.
*
* @param    ceBtree_Compare (*cmpfn)(void *, void *)
*           - pointer to a user defined function, which is used
*             for key comparisons.
*
* @return   ceBtree *
**/
ceBtree *ceBtree_Init(
        ceBtree_Compare (*cmpfn)(void *, void *),
        void (*freefn)(ceBtreeNode *)) {
    
    ceBtree *tree = (ceBtree *)
        malloc(sizeof(ceBtree));
    
    if (tree == NULL) {
        return NULL;
    }
    
    tree->root = NULL;
    tree->cmpfn = cmpfn;
    tree->freefn = freefn;
    tree->is_redblack = 0;
    
    return tree;
}

/**
* See if key exists in tree, or subset start if not NULL.
*
* @param    ceBtree *tree
* @param    ceBtree *start. If start is NULL, start = tree->root
* @param    void *key
* @return   int 1 if key exists
**/
int ceBtree_KeyExists(ceBtree *tree, ceBtreeNode *start, void *key)
{
    // Auto set to tree root when NULL
    if (start == NULL) {
        start = tree->root;
    }
    
    ceBtreeNode *cur = start;
    int res;
    
    while (1) {
        res = tree->cmpfn(key, cur->key);
        if (res == CE_BTREE_COMPARE_GT) {
            if (cur->right == NULL) {
                return 0;
            }
            
            cur = cur->right;
        } else if (res == CE_BTREE_COMPARE_LT) {
            if (cur->left == NULL) {
                return 0;
            }
            
            cur = cur->left;
        } else if (res == CE_BTREE_COMPARE_EQ) {
            return 1;
        }
    }
    
    return 0;
}

/**
* Perform a left rotation
*
* @param    ceBtree *tree
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_RotateLeft(ceBtree *tree)
{
    ceBtreeNode *cur,
                *oldroot;
    
    // Can't rotate anymore
    if (tree->root == NULL || tree->root->right == NULL) {
        return CE_BTREE_STATUS_OK;
    }
    
    // Pointer to oldroot
    oldroot = tree->root;
    
    // Set new root
    tree->root = tree->root->right;
    tree->root->parent = NULL;
    
    // Break apart from tree
    oldroot->right = NULL;
    
    // Find left-most leaf
    cur = tree->root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    
    // Link trees back together
    cur->left = oldroot;
    cur->left->parent = cur;
    
    return CE_BTREE_STATUS_OK;
}

/**
* Perform a right rotation
*
* @param    ceBtree *tree
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_RotateRight(ceBtree *tree)
{
    ceBtreeNode *cur,
                *oldroot;
    
    // Can't rotate anymore
    if (tree->root == NULL || tree->root->left == NULL) {
        return CE_BTREE_STATUS_OK;
    }
    
    // Pointer to oldroot
    oldroot = tree->root;
    
    // Set new root
    tree->root = tree->root->left;
    tree->root->parent = NULL;
    
    // Break apart from tree
    oldroot->left = NULL;
    
    // Find right-most leaf
    cur = tree->root;
    while (cur->right != NULL) {
        cur = cur->right;
    }
    
    // Link trees back together
    cur->right = oldroot;
    cur->right->parent = cur;
    
    return CE_BTREE_STATUS_OK;
}

/**
* Free a tree structure
*
* @param    ceBtree **tree
* @return   void
**/
void ceBtree_Free(ceBtree **tree)
{
    // Dereference **tree, so we can access it
    ceBtree *realtree = (ceBtree *)(*tree);
    
    // Set pointer to current node
    ceBtreeNode *cur = realtree->root;
    
    // Initialize side to -1
    int side = -1;

    if (realtree->root != NULL) {
        while (1) {
            if (cur->left != NULL) {
                // Recurse down the left side of the tree
                cur = cur->left;
                side = 1;
                continue;
            }
        
            if (cur->right != NULL) {
                // Recurse down the right side of the tree
                cur = cur->right;
                side = 2;
                continue;
            }
        
            /* If parent == NULL, then we've ascended back to the root
               node of the tree. In this case, we break out of the loop. */
            if (cur->parent == NULL) {
                break;
            }
        
            // Ascend to parent
            cur = cur->parent;
        
            if (side == 1) {
                // Free left side
                if (realtree->freefn != NULL) {
                    realtree->freefn(cur->left);
                }
                
                free(cur->left);
                cur->left = NULL;
            } else {
                // Free right side
                if (realtree->freefn != NULL) {
                    realtree->freefn(cur->right);
                }
                
                free(cur->right);
                cur->right = NULL;
            }
        
            /* Figure out what side we were just on, in relation to the
               parent node. If this step is omitted, we may lose track
               of which node should be free'd on the next loop. */
            if (cur->parent != NULL) {
                if (cur->parent->left == cur) {
                    side = 1;
                } else {
                    side = 2;
                }
            }
        }

        // Free the root node
        if (realtree->root != NULL) {
            if (realtree->freefn != NULL) {
                realtree->freefn(realtree->root);
            }
            
            free(realtree->root);
            realtree->root = NULL;
        }
    }

    // Free the tree
    free(*tree);
    *tree = NULL;
}
