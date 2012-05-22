#include <stdio.h>
#include <btree.h>

static int ceIsValidBtreeHelp(ceBtree *tree, ceBtreeNode *cur, ceBtreeNode *prev);

/**
* Verify that tree is a valid Binary Tree, in O(n) time. Helper function.
*
* @param    ceBtree *tree
* @param    ceBtreeNode *cur
* @param    ceBtreeNode *prev
* @return   1 if tree is valid, otherwise 0
**/
static int ceIsValidBtreeHelp(ceBtree *tree, ceBtreeNode *cur, ceBtreeNode *prev)
{
    if (cur) {
        // Recurse down left side
        if (!ceIsValidBtreeHelp(tree, cur->left, NULL)) {
            return 0;
        }
        
        if (prev) {
            ceBtree_Compare res = tree->cmpfn(cur->key, prev->key);
            if (res != CE_BTREE_COMPARE_GT) {
                return 0;
            }
        }
        
        // Recurse down right side
        return ceIsValidBtreeHelp(tree, cur->right, cur);
    }
    
    return 1;
}

/**
* Verify that tree is a valid Binary Tree, in O(n) time.
*
* @param    ceBtree *tree
* @return   1 if tree is valid, otherwise 0
**/
int ceIsValidBtree(ceBtree *tree)
{
    return ceIsValidBtreeHelp(tree, tree->root, NULL);
}
