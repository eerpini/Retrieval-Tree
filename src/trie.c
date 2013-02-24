#include <trie.h>
#include <linkedlist.h>

/*
 * Creates a trie and allocates the root node with an empty string
 */
trie * trie_create (){
        trie * temp = malloc(sizeof(trie));
        temp->root = trie_createnode(NULL, 0);
        temp->num_strings = 0;
        return temp;
}

/*
 * Creates a new trienode, makes a copy of the data
 */
trienode * trie_createnode(char * value, int len){
        trienode * temp = malloc(sizeof(trienode));
        //Allocate the children linked list lazily
        temp->children = NULL;
        if(value != NULL){
                temp->num_strings = 1;
                temp->is_word = TRUE;
                temp->value = malloc(sizeof(char) * (len + 1));
                strncpy(temp->value, value, len);
                temp->value[len] = 0;
        }
        else{
                log("Creating empty root node at %p\n", temp);
                temp->num_strings = 0;
                temp->is_word = FALSE;
                temp->value = NULL;
        }

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
        if(parent->children == NULL){
                parent->children = ll_create();
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
        if(parent == NULL || parent->children == NULL){
                return NULL;
        }

        return ll_get_nodes(parent->children);
}

/*
 * Return the number of children
 */
int trie_num_children (trienode * parent){
        if(parent == NULL){
                return FAILURE;
        }
        return ll_length(parent->children);
}
