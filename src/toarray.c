#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

/**
* Convert binary tree to array, in ascending order. This is exactly the same
* algorithm as recursive in-order traversal, only it's iterative.
*
* @param    ceBtree *tree
* @param    int *len
*               - Pointer to int, which will hold array len
* @return   ceBtreeNode **
**/
ceBtreeNode **ceBtreeToArray(ceBtree *tree, int *len)
{
    // If this function returns prematurly, len won't be an arbitrary
    // number
    *len = 0;

    // Check errors
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }
    
    // Array, stack, temporary pointer
    ceBtreeNode **array,
                **stack,
                **tmp = NULL;
    
    // Nodes we keep pointers to
    ceBtreeNode *cur = tree->root;
    
    // Array size/len/stack len
    unsigned int    size = CE_BTREE_ARRAY_CHUNK,
                    arraylen = 0,
                    stacklen = 0;
    
    // Alloc
    array = (ceBtreeNode **)
            malloc(sizeof(ceBtreeNode *) * size);

    // Alloc
    stack = (ceBtreeNode **)
            malloc(sizeof(ceBtreeNode *) * size);
    
    if (array == NULL || stack == NULL) {
        goto cleanup_error;
    }
    
    while (1) {
        if (cur) {
            // Push
            stack[stacklen++] = cur;
            cur = cur->left;
        } else {
            if (stacklen == 0) {
                break;
            } else {
                // Pop
                cur = stack[--stacklen];
                
                // Append Node
                array[arraylen++] = cur;
                
                // Allocate mode memory?
                if (arraylen >= size) {
                    size += CE_BTREE_ARRAY_CHUNK;
                    tmp = (ceBtreeNode **)
                        realloc(array, sizeof(ceBtreeNode *) * size);

                    if (tmp == NULL) {
                        goto cleanup_error;
                    }
        
                    array = tmp;
                }
                
                cur = cur->right;
            }
        }
    }
    
    free(stack);
    
    *len = arraylen;
    return array;
    
    cleanup_error:
        free(array);
        free(stack);
        return NULL;
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
