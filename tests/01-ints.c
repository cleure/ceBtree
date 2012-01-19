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
        ceBtree_Insert(tree, (void *)ptr, (void *)ptr, 1);
    }
    
    cur = tree->root;
    
    i = 41;
    ceBtree_Remove(tree, NULL, (void *)&i);
    
    int len;
    array = ceBtreeToArray(tree, tree->root, &len);
    //printf("Len: %d\n", len);
    
    for (i = 0; i < len; ++i) {
        printf("%d\n", *((int *)array[i]->key));
    }
    
    ceBtreeToArray_Free(&array);
    ceBtree_Free(&tree);

    return 0;
}
