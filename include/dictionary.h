#include "commondefs.h"
#include "cmdutils.h"
#include "trie.h"

#ifndef DICTIONARY_SEEN
#define DICTIONARY_SEEN

#define MAX_WORD_SIZE (1024 - 6 -1) 

typedef struct prefix_lookup {
        int len;
        void ** matches;
}lookup;

dict *  new_dictionary          ();

bool    _insert_word_recur      (trienode *, char *, int );
bool    insert                  (dict *, char *, int);
void    _print_words_recur      (trienode *, int);
void    print                   (dict *);
int     _num_strings_in_subtree_recur (trienode *);
int     word_count              (dict *);
bool    _find_recur             (trienode *, char *, lookup *);
bool    find                    (dict *, char *);


#endif
