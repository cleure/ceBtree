#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

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
    tree->insert = ceBtree_Insert;
    tree->remove = ceBtree_Remove;
    
    return tree;
}

/**
* Initialize a new rbtree.
*
* @param    ceBtree_Compare (*cmpfn)(void *, void *)
*           - pointer to a user defined function, which is used
*             for key comparisons.
*
* @return   ceBtree *
**/
ceBtree *ceRBtree_Init(
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
    tree->is_redblack = 1;
    
    tree->insert = ceRBtree_Insert;
    // FIXME
    tree->remove = ceBtree_Remove;
    
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
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    // Auto set to tree root when NULL
    if (start == NULL) {
        start = tree->root;
    }

    ceBtreeNode *cur = tree->root;
    ceBtree_Status cmp;
    
    while (NULL != cur) {
        cmp = tree->cmpfn(key, cur->key);
        
        if (cmp == CE_BTREE_COMPARE_GT) {
            cur = cur->right;
        } else if (cmp == CE_BTREE_COMPARE_LT) {
            cur = cur->left;
        } else if (cmp == CE_BTREE_COMPARE_EQ) {
            return 1;
        } else {
            break;
        }
    }
    
    return 0;
}

/**
* Search tree for node. Retuns NULL on error, or if not found.
*
* @param    ceBtree *tree
* @param    void *key
* @return   ceBteeNode *
**/
ceBtreeNode *ceBtree_Find(ceBtree *tree, void *key)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    ceBtreeNode *cur = tree->root;
    ceBtree_Status cmp;
    
    while (NULL != cur) {
        cmp = tree->cmpfn(key, cur->key);
        
        if (cmp == CE_BTREE_COMPARE_GT) {
            cur = cur->right;
        } else if (cmp == CE_BTREE_COMPARE_LT) {
            cur = cur->left;
        } else if (cmp == CE_BTREE_COMPARE_EQ) {
            return cur;
        } else {
            break;
        }
    }
    
    return NULL;
}

/**
* Find minumum.
*
* @param    ceBtree *tree
* @return   ceBtreeNode *
**/
ceBtreeNode *ceBtree_Min(ceBtree *tree)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }
    
    ceBtreeNode *cur = tree->root;
    while (cur->left) {
        cur = cur->left;
    }
    
    return cur;
}

/**
* Find maximum.
*
* @param    ceBtree *tree
* @return   ceBtreeNode *
**/
ceBtreeNode *ceBtree_Max(ceBtree *tree)
{
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }
    
    ceBtreeNode *cur = tree->root;
    while (cur->right) {
        cur = cur->right;
    }
    
    return cur;
}

/**
* Perform a left rotation
*
* @param    ceBtree *tree
* @param    ceBtreeNode *x  - Node to rotate. NULL for root.
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_RotateLeft(ceBtree *tree, ceBtreeNode *x)
{
    ceBtreeNode *y;
    
    // If x is NULL, set to root
    if (x == NULL) {
        x = tree->root;
    }
    
    // Can't rotate
    if (tree->root == NULL || x->right == NULL) {
        return CE_BTREE_STATUS_OK;
    }
    
    // y is x->right
    y = x->right;
    
    // Move y's left subtree to x's right subtree, to free it up
    x->right = y->left;
    if (x->right != NULL) {
        x->right->parent = x;
    }
    
    // Move x to y's left subtree
    y->left = x;
    if (x == tree->root) {
        // If x is the root node
        y->parent = NULL;
        x->parent = y;
        tree->root = y;
    } else {
        if (x->parent->left == x) {
            // x is the left subtree of it's parent
            x->parent->left = y;
        } else {
            // x is the right subtree of it's parent
            x->parent->right = y;
        }
        
        // Setup parent pointers
        y->parent = x->parent;
        x->parent = y;
    }
    
    return CE_BTREE_STATUS_OK;
}

/**
* Perform a right rotation
*
* @param    ceBtree *tree
* @param    ceBtreeNode *x  - Node to rotate. NULL for root.
* @return   ceBtree_Status
**/
ceBtree_Status ceBtree_RotateRight(ceBtree *tree, ceBtreeNode *x)
{
    ceBtreeNode *y;
    
    // If x is NULL, set to root
    if (x == NULL) {
        x = tree->root;
    }
    
    // Can't rotate
    if (tree->root == NULL || x->left == NULL) {
        return CE_BTREE_STATUS_OK;
    }
    
    // y is x->left
    y = x->left;
    
    // Move y's right subtree to x's left subtree, to free it up
    x->left = y->right;
    if (x->left != NULL) {
        x->left->parent = x;
    }
    
    // Move x to y's right subtree
    y->right = x;
    if (x == tree->root) {
        // If x is the root node
        y->parent = NULL;
        x->parent = y;
        tree->root = y;
    } else {
        if (x->parent->left == x) {
            // x is the left subtree of it's parent
            x->parent->left = y;
        } else {
            // x is the right subtree of it's parent
            x->parent->right = y;
        }
        
        // Setup parent pointers
        y->parent = x->parent;
        x->parent = y;
    }
    
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
