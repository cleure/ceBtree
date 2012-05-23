#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

/**
* Helper function to get remaining work
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @param    ceBtreeNode *last_append
* @return   int, bits (1 == left_work, 2 == right_work)
**/
static int getWork(
        ceBtree *tree,
        ceBtreeNode *cur,
        ceBtreeNode *last_append) {
    
    ceBtree_Compare res;
    int left_work = 0,
        right_work = 0;

    if (cur->left != NULL) {
        res = tree->cmpfn(cur->left->key, last_append->key);
        if (res == CE_BTREE_COMPARE_GT) {
            left_work = 1;
        }
    }

    if (cur->right != NULL) {
        res = tree->cmpfn(cur->right->key, last_append->key);
        if (res == CE_BTREE_COMPARE_GT) {
            right_work = 2;
        }
    }

    return left_work | right_work;
}

/**
* Helper function to check if node has been added.
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @param    ceBtreeNode *last_append
* @return   int, (1 == yes, 0 == no)
**/
static int nodeHasBeenAdded(
        ceBtree *tree,
        ceBtreeNode *cur,
        ceBtreeNode *last_append) {
    
    ceBtree_Compare res;
    if (cur == NULL || last_append == NULL) {
        return 0;
    }

    res = tree->cmpfn(cur->key, last_append->key);
    if (res == CE_BTREE_COMPARE_LT || res == CE_BTREE_COMPARE_EQ) {
        return 1;
    }

    return 0;
}

#define APPEND_CUR_NODE()\
    array[arraylen] = cur;\
    last_append = cur;\
    arraylen++;\
    \
    if (arraylen >= size) {\
        size += CE_BTREE_ARRAY_CHUNK;\
        tmp = (ceBtreeNode **)\
              realloc(array, sizeof(ceBtreeNode *) * size);\
        \
        \
        if (tmp == NULL) {\
            free(array);\
            return NULL;\
        }\
        \
        array = tmp;\
    }

/**
* Convert binary tree to array, in ascending order.
*
* @param    ceBtreeNode *root
* @param    int *len
*               - Pointer to int, which will hold array len
* @return   ceBtreeNode **
**/
ceBtreeNode **ceBtreeToArray(ceBtree *tree, ceBtreeNode *root, int *len)
{
    // If this function returns prematurly, len won't be an arbitrary
    // number
    *len = 0;

    // Check errors
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }
    
    // Array, and tempory space
    ceBtreeNode **array,
                **tmp = NULL;
    
    // Nodes we keep pointers to
    ceBtreeNode *cur = tree->root,
                *rightmost = tree->root,
                *last_append = NULL;
    
    // Array size/len
    int size = CE_BTREE_ARRAY_CHUNK,
        arraylen = 0;
    
    // Alloc
    array = (ceBtreeNode **)
            malloc(sizeof(ceBtreeNode *) * size);
    
    if (array == NULL) {
        return NULL;
    }
    
    // Set cur to left-most
    while (cur->left) {
        cur = cur->left;
    }
    
    // Set rightmost to right-most
    while (rightmost->right) {
        rightmost = rightmost->right;
    }
    
    // Append first
    APPEND_CUR_NODE();
    
    while (1) {
        int work = getWork(tree, cur, last_append);
        if (!work) {
            // Reached the final in-order node
            if (cur == rightmost) {
                break;
            }
        
            cur = cur->parent;
            if (!nodeHasBeenAdded(tree, cur, last_append)) {
                APPEND_CUR_NODE();
            }
        } else if (work & 1) {
            while (cur->left) {
                cur = cur->left;
            }
            
            APPEND_CUR_NODE();
        } else if (work & 2) {
            cur = cur->right;
            if (cur->left && !nodeHasBeenAdded(tree, cur->left, last_append)) {
                continue;
            }
            
            APPEND_CUR_NODE();
        }
    }
    
    *len = arraylen;
    return array;
}

/**
* Free array to pointers, created by ceBtreeToArray().
*
* @param    ceBtreeNode ***array
* @return   void
**/
void ceBtreeToArray_Free(ceBtreeNode ***array)
{
    free(*array);
    *array = NULL;
}
