#ifndef CE_BTREE_DOT_H
#define CE_BTREE_DOT_H

#include <stdint.h>

// Used when converting a Btree to an Array of nodes
#define CE_BTREE_ARRAY_CHUNK 16384

// Define black and red colors
#define CE_BTREE_COLOR_BLACK 0
#define CE_BTREE_COLOR_RED 1

/* Define color type. A typedef for u_char is used instead of an enum
   because the size of an enum can be as large as 4 bytes. */
typedef uint8_t ceBtree_Color;

// Enum returned by comparison function pointers
enum ceBtree_Compare {
    CE_BTREE_COMPARE_EQ,
    CE_BTREE_COMPARE_GT,
    CE_BTREE_COMPARE_LT,
    CE_BTREE_COMPARE_ERR
};

// Enum returned by various functions
enum ceBtree_Status {
    CE_BTREE_STATUS_OK,
    CE_BTREE_STATUS_ERR
};

typedef enum ceBtree_Compare ceBtree_Compare;
typedef enum ceBtree_Status ceBtree_Status;

// Tree node data structure
struct ceBtreeNode {
    void *key;
    void *data;
    
    struct ceBtreeNode *left;
    struct ceBtreeNode *right;
    struct ceBtreeNode *parent;
    
    ceBtree_Color color;
};

typedef struct ceBtreeNode ceBtreeNode;

// Tree
struct ceBtree {
    // Root
    struct ceBtreeNode *root;
    
    // Compare function pointer
    ceBtree_Compare (*cmpfn)(void *, void *);
    
    // Free function pointer
    void (*freefn)(ceBtreeNode *);
    
    // Is red black tree?
    uint8_t is_redblack;
};

typedef struct ceBtree ceBtree;

ceBtree *ceBtree_Init(
    ceBtree_Compare (*cmpfn)(void *, void *),
    void (*freefn)(ceBtreeNode *));

ceBtree_Status ceBtree_Insert(ceBtree *tree, void *key, void *data, int replace);
ceBtree_Status ceBtree_Remove(ceBtree *tree, ceBtreeNode *start, void *key);
int ceBtree_KeyExists(ceBtree *tree, ceBtreeNode *start, void *key);

// Functions, for converting Btree to Array
ceBtreeNode **ceBtreeToArray(ceBtree *tree, ceBtreeNode *root, int *len);
void ceBtreeToArray_Free(ceBtreeNode ***array);

// String compare
ceBtree_Compare ceBtreeStrcmp(void *A, void *B);

// Int compare
ceBtree_Compare ceBtreeIntcmp(void *A, void *B);

// Free functions
void ceBtreeNode_Free(ceBtreeNode *node);
void ceBtree_Free(ceBtree **tree);

#endif