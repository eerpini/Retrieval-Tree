#include <trie.h>
#include <linkedlist.h>

/*
 * Creates a trie and allocates the root node with an empty string
 */
trie * trie_create (){
        trie * temp = malloc(sizeof(trie));
        temp->root = trie_createnode(NULL);
        temp->num_strings = 0;
        return temp;
}

/*
 * Creates a new trienode, uses the data provided, no copy is created.
 */
trienode * trie_createnode(char * value){
        trienode * temp = malloc(sizeof(trienode));
        //Allocate the children linked list lazily
        temp->children = NULL;
        if(value != NULL){
                temp->num_strings = 1;
                temp->is_word = TRUE;
        }
        else{
                temp->num_strings = 0;
                temp->is_word = FALSE;
        }
        temp->value = value;
        return temp;
}

/*
 * Frees a trienode
 */
void trie_freenode( trienode * node){
        if(node == NULL){
                return;
        }
        ll_free(node->children);
        if(node->value != NULL){
                free(node->value);
        }

        free(node);
        return;
}

void trie_add_child(trienode * parent, trienode *child){
        if(parent == NULL || child == NULL){
                return;
        }

        ll_add(parent->children, child);
        return;
}

/*
 * Just removes the trienode from the children, does not free any of the data
 */
int trie_remove_child(trienode *parent, trienode *child){
        if(parent == NULL || child == NULL){
                return 0;
        }

        return ll_remove(parent->children, child, FALSE);
}

/*
 * Gets the children for a trienode as an array of trienode pointers
 */
void ** trie_get_children (trienode * parent){
        if(parent == NULL){
                return NULL;
        }

        return ll_get_nodes(parent->children);
}
