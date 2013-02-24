#include <commondefs.h>
#include <linkedlist.h>

#ifndef TRIE_SEEN
#define TRIE_SEEN

typedef struct {
        ll * children;
        int num_strings;
        char * value;
        char is_word;

}trienode;


typedef struct retrieval_tree {
        trienode *root;
        int num_strings;
}trie;

trie * create_trie ();
trienode * create_trienode (char *);
int add_child(trienode* );
void remove_child(trienode *);
int get_children(trienode *);


#endif

