#ifndef CE_BTREE_CONTRIB_DOT_H
#define CE_BTREE_CONTRIB_DOT_H

/* The contents of this file are NOT ANSI-C Compatible. Compatibility is not
   guaranteed. */

#ifndef typeof
  #define typeof __typeof__
#endif

/* Static function versions. This allows you to use certain functions without
   the need for a temporary void* pointer. For instance, instead of writing:
   
     char *str = "my_key";
     ceBtreeNode *match = ceBtree_Find(tree, (void *)str);
     
   you can write:
     ceBtreeNode *match = ceBtree_Find_S(tree, "my_key");
   
   which is useful if you just want to write a block of code that checks for
   a couple different keys:
   
     if (!ceBtree_KeyExists_S(tree, NULL, "installed")) {
        ...
     }
     
     if (!ceBtree_KeyExists_S(tree, NULL, "configured")) {
        ...
     }
*/

#define ceBtree_Find_S(in_tree, in_arg) ({\
    typeof (in_arg) tmp = in_arg;\
    void *ptr = (void *)&tmp;\
    ceBtree_Find(in_tree, ptr);\
})

#define ceBtree_KeyExists_S(in_tree, in_start, in_arg) ({\
    typeof (in_arg) tmp = in_arg;\
    void *ptr = (void *)&tmp;\
    ceBtree_KeyExists(in_tree, in_start, ptr);\
})

#endif