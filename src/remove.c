#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

/*

TODO: Clean this up. It might be possible to use #define to make function
      macros to handle each individual case, which would clean things up
      without having to jump to an actual function.

*/

/**
* Delete Case 1 helper function
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @return   void
**/
static void BST_DeleteCase1(ceBtree *tree, ceBtreeNode *cur)
{
    ceBtreeNode *parent;

    if (cur->parent == NULL) {
        // Special case for parent
        free(tree->root);
        tree->root = NULL;
    } else {
        // Free non-root node
        parent = cur->parent;
        if (parent->left == cur) {
            free(parent->left);
            parent->left = NULL;
        } else {
            free(parent->right);
            parent->right = NULL;
        }
    }
}

/**
* Delete Case 2 helper function
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @return   void
**/
static void BST_DeleteCase2(ceBtree *tree, ceBtreeNode *cur)
{
    ceBtreeNode *parent = cur->parent;

    if (cur->left != NULL) {
        cur = cur->left;
    } else {
        cur = cur->right;
    }
    
    if (parent == NULL) {
        // Special case, if root node
        free(tree->root);
        tree->root = cur;
        tree->root->parent = NULL;
    } else {
        // Normal case
        if (parent->left == cur->parent) {
            free(parent->left);
            parent->left = cur;
        } else {
            free(parent->right);
            parent->right = cur;
        }

        cur->parent = parent;
    }
}

/**
* Delete Case 3 helper function
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @return   void
**/
static void BST_DeleteCase3(ceBtree *tree, ceBtreeNode *cur)
{
    ceBtreeNode *replacement = cur->right,
                *right = NULL,
                *parent = NULL;

    // Find a node with no left children
    while (replacement->left != NULL) {
        replacement = replacement->left;
    }

    // Pointer to parent
    parent = replacement->parent;

    // Set cur's key/data pointers to the replacement's
    cur->key = replacement->key;
    cur->data = replacement->data;

    if (replacement->right != NULL) {
        /* The replacement has a right child, so we have to replace it
           with it's child, after freeing. */

        right = replacement->right;
        right->parent = parent;
        if (replacement == parent->right) {
            free(parent->right);
            parent->right = right;
        } else {
            free(parent->left);
            parent->left = right;
        }
    } else {
        // Replacement has no right child.
        if (replacement == parent->right) {
            free(parent->right);
            parent->right = NULL;
        } else {
            free(parent->left);
            parent->left = NULL;
        }
    }
}

/**
* Remove node from tree.
*
* @param    ceBtree *tree
* @param    ceBtreeNode *start
* @param    void *key
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_Remove(ceBtree *tree, ceBtreeNode *start, void *key)
{
    // Auto set to tree root when NULL
    if (start == NULL) {
        start = tree->root;
    }

    int res;
    ceBtreeNode *cur, *parent;
    cur = start;
    
    while (cur != NULL) {
    
        // Traverse until key matches, or end is reached
        res = tree->cmpfn(cur->key, key);
        if (res == CE_BTREE_COMPARE_GT) {
            cur = cur->left;            
            continue;
        } else if (res == CE_BTREE_COMPARE_LT) {
            cur = cur->right;
            continue;
        }
        
        if (res == CE_BTREE_COMPARE_EQ) {
        
            // Free node data
            if (tree->freefn != NULL) {
                tree->freefn(cur);
            }
        
            /* Remove node. There's 3 different cases that are handled here:
               1) Node has no children
                    - Node simply be removed without incident
               2) Node has one child
                    - Node can be removed and replaced by it's child
               3) Node has two children
                    - The left side of the node's right sub-tree is traversed
                      until a node with no left children is found. The value
                      of the current node is replaced with the value of this
                      node, and the child is either free'd or replaced by it's
                      child. */
            if (cur->left == NULL && cur->right == NULL) {
                // Case 1) Node has no children
                BST_DeleteCase1(tree, cur);
            } else if (cur->left != NULL && cur->right != NULL) {
                // Case 3) Node has 2 children
                BST_DeleteCase3(tree, cur);
            } else {
                // Case 2) Node has 1 child
                BST_DeleteCase2(tree, cur);
            }
            
            return CE_BTREE_STATUS_OK;
        }
    }
    
    return CE_BTREE_STATUS_ERR;
}

/*

- Delete node, as if it were a regular Binary Tree

Red Black Tree Cases:
    - If deleted node was red, do nothing
    - If deleted node was black, find a red node and recolor it black
    - If no red node can be found, rotate and recolor


*/
