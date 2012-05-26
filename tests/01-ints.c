#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

                     16
                   /    \
                  10    18
                 /  \   / \
                5   12 17  22
               / \ /  \    / \
              3  6 11  14  20 30
             / \      /     \   \
            1   4    13      21  41
                                 /
                                38

*/

int arrr[] = {
    16, 10, 18, 5, 12, 17, 22, 3, 6, 11, 14, 20, 30, 1, 4, 13, 21, 41, 38
};

void my_free_function(ceBtreeNode *node)
{
    free(node->data);
    node->key = NULL;
    node->data = NULL;
}

/*

enum ceBtree_Compare {
    CE_BTREE_COMPARE_EQ,
    CE_BTREE_COMPARE_GT,
    CE_BTREE_COMPARE_LT,
    CE_BTREE_COMPARE_ERR
};

                     16
                   /    \
                  10    18
                 /  \   / \
                5   12 17  22
               / \ /  \    / \
              3  6 11  14  20 30
             / \      /     \   \
            1   4    13      21  41
                                 /
                                38

*/

/*

//
// In-Order traversal, by converting tree to threaded binary tree
//
void in_order(ceBtreeNode *node)
{
    if (node == NULL) return;
    ceBtreeNode *cur = node,
                *pre;
    
    while (cur != NULL) {
        if (cur->left == NULL) {
            printf("%d\n", *((int *)cur->key));
            cur = cur->right;
        } else {
            pre = cur->left;
            while (pre->right != NULL && pre->right != cur) {
                pre = pre->right;
            }
            
            if (pre->right == NULL) {
                pre->right = cur;
                cur = cur->left;
            } else {
                pre->right = NULL;
                printf("%d\n", *((int *)cur->key));
                cur = cur->right;
            }
        }
    }
}*/

int main(int argc, char **argv)
{
    ceBtreeNode *cur;
    ceBtreeNode **array;
    ceBtree *tree = ceBtree_Init(
        ceBtreeIntcmp,
        my_free_function);
    
    int i, l;
    l = sizeof(arrr) / sizeof(arrr[0]);
    for (i = 0; i < l; ++i) {
        int *ptr = malloc(sizeof(int));
        *ptr = arrr[i];
        tree->insert(tree, (void *)ptr, (void *)ptr, 1);
    }
    
    cur = tree->root;
    
    int len;
    array = ceBtreeToArray(tree, &len);
    //printf("Len: %d\n", len);
    
    for (i = 0; i < len; ++i) {
        printf("%d\n", *((int *)array[i]->key));
    }
    
    ceBtreeToArray_Free(&array);
    ceBtree_Free(&tree);

    return 0;
}
