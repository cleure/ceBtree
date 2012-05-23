#include "btree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int arrr[] = {
    30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70
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
    ceBtree *tree = ceRBtree_Init(
        ceBtreeIntcmp,
        my_free_function);
    
    int i, l;
    l = sizeof(arrr) / sizeof(arrr[0]);
    for (i = 0; i < l; ++i) {
        int *ptr = malloc(sizeof(int));
        *ptr = arrr[i];
        tree->insert(tree, (void *)ptr, (void *)ptr, 1);
    }
    
    // Test right height
    int height;
    cur = tree->root;
    height = 0;
    while (cur->right != NULL) {
        cur = cur->right;
        height++;
    }
    
    printf("Right Height: %d\n", height);
    
    i = 30;
    while (i < 50) {
        tree->remove(tree, NULL, (void *)&i);
        i+= 2;
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
