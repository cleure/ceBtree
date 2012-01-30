#include "btree.h"
#include "helpers.h"
#include <stdlib.h>

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
    // Auto set to tree root when NULL
    if (root == NULL) {
        root = tree->root;
    }

    // These will be used for looping
    int not_in_array, skip_lookup, alen;
    
    // Size of array, so we know when to reallocate
    int size = CE_BTREE_ARRAY_CHUNK;
    
    // Used for binary search
    int first, last;
    
    // Pointer to current node
    ceBtreeNode *cur;
    
    // Destination array
    ceBtreeNode **dest = (ceBtreeNode **)
        malloc(sizeof(ceBtreeNode *) * size);
    
    // Used for reallocation
    ceBtreeNode **tmp_dest = NULL;
    
    // Handle OOM
    if (dest == NULL) {
        return NULL;
    }
    
    // Initialize some variables
    alen = 0;
    skip_lookup = 0;
    
    // Descend to left-most node
    cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    
    // Traverse tree
    while (1) {
        /* When skip_lookup is positive, we don't check that cur is already
           in **dest, because that has already been confirmed. */
        
        if (!skip_lookup) {
            not_in_array = 1;
            
            // Reset these
            first = 0,
            last = (alen - 1);
            
            /* Check if cur is in **dest. This uses Binary Search, as it's
               much faster for anything with over 50 elements. It compares
               the keys, using the compare function pointer on the tree. */
            while (first <= last) {
                int mid, res;
                mid = (first + last) / 2;
                res = tree->cmpfn(dest[mid]->key, cur->key);
                
                if (res == CE_BTREE_COMPARE_GT) {
                    last = mid - 1;
                } else if (res == CE_BTREE_COMPARE_LT) {
                    first = mid + 1;
                } else if (res == CE_BTREE_COMPARE_EQ) {
                    not_in_array = 0;
                    break;
                }
            }
        } else {
            // Reset skip_lookup
            skip_lookup = 0;
        }
        
        // Temporary variables
        int left_in_array = 0,
            right_in_array = 0;
        
        // No need to check if they're both NULL
        if (cur->left != NULL || cur->right != NULL) {
            
            // Check if cur->left is in array, using Binary Search
            if (cur->left != NULL) {
                first = 0,
                last = (alen - 1);
            
                // Binary search
                while (first <= last) {
                    int mid, res;
                    mid = (first + last) / 2;
                    res = tree->cmpfn(dest[mid]->key, cur->left->key);
                    
                    if (res == CE_BTREE_COMPARE_GT) {
                        last = mid - 1;
                    } else if (res == CE_BTREE_COMPARE_LT) {
                        first = mid + 1;
                    } else if (res == CE_BTREE_COMPARE_EQ) {
                        left_in_array = 1;
                        break;
                    }
                }
            }
            
            // Check if cur->right is in array, using Binary Search
            if (cur->right != NULL) {
                first = 0,
                last = (alen - 1);
            
                // Binary search
                while (first <= last) {
                    int mid, res;
                    mid = (first + last) / 2;
                    res = tree->cmpfn(dest[mid]->key, cur->right->key);
                    
                    if (res == CE_BTREE_COMPARE_GT) {
                        last = mid - 1;
                    } else if (res == CE_BTREE_COMPARE_LT) {
                        first = mid + 1;
                    } else if (res == CE_BTREE_COMPARE_EQ) {
                        right_in_array = 1;
                        break;
                    }
                }
            }
            
        }
        
        /* If the node isn't already in the array, and the left side has
           already been added, then add it. */
        if (not_in_array && (cur->left == NULL || left_in_array)) {
            dest[alen] = cur;
            ++alen;
            
            // Make sure we have enough memory. Reallocate if needed
            if (alen == size) {
                size = size + CE_BTREE_ARRAY_CHUNK;
                tmp_dest = realloc(dest,
                    sizeof(ceBtreeNode *) * size);
                
                // Handle OOM
                if (tmp_dest == NULL) {
                    free(dest);
                    return NULL;
                }
                
                dest = tmp_dest;
            }
        }
        
        if (cur->left != NULL && !left_in_array) {
            /* We've confirmed that cur->left is not in the array. Set
               variables, and continue from top, where it will be added. */
                
            skip_lookup = 1;
            not_in_array = 1;
            cur = cur->left;
            continue;
        }
        
        if (cur->right != NULL && !right_in_array) {
            /* We've confirmed that cur->right is not in the array. Set
               variables, and continue from top, where it will be added. */
                
            skip_lookup = 1;
            not_in_array = 1;
            cur = cur->right;
            continue;
        }
        
        /* This will only be reached, and true, when every node has been added
           to the array. */
        if (cur == root) {
            break;
        }
        
        // Ascend to parent
        cur = cur->parent;
    }
    
    // Set value of len pointer
    *len = alen;
    
    return dest;
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
