#include <commondefs.h>
#include <linkedlist.h>

#ifndef TRIE_SEEN
#define TRIE_SEEN

typedef struct {
        ll * children;
        int num_strings;
        char * value;
        bool is_word;

}trienode;


typedef struct retrieval_tree {
        trienode *root;
        int num_strings;
}trie;

typedef trie dict;

trie *          trie_create             ();
trienode *      trie_createnode         (char *, int);
void            trie_freenode           (trienode *);
void            trie_add_child          (trienode *, trienode* );
int             trie_remove_child       (trienode *, trienode *);
//Return an array of pointers to the child trienodes
void **         trie_get_children       (trienode *);
int             trie_num_children       (trienode *);

#endif

