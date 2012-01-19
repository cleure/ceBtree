#ifndef CE_BTREE_HELPERS_DOT_H
#define CE_BTREE_HELPERS_DOT_H

// This macro function is used to initialize newly created nodes
#define ceBtreeNodeInit(node, key, data)\
    node->key = key;\
    node->data = data;\
    node->left = NULL;\
    node->right = NULL;

#endif