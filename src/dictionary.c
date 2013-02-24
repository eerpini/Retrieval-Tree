#include <dictionary.h>
#include <cmdutils.h>
#include <strutils.h>

dict * new_dictionary (){
        return (dict *)trie_create();
}

/*
 * Recursive call to insert a word
 */
bool _insert_word_recur(trienode * root, char *word, int wlen){

        int i;
        /*
         * if no match is found return false
         * If exact match return true
         * if I am the prefix, check children
         *      if all children return false
         *              add new child with suffix
         *      if some child return true 
         *              return true
         * if I am a partial match, split myself
         *      push unmatching suffix as new child and parent of my children
         *      push unmatching suffix in word as my new child
         */
        void ** children;
        int match_index = strcmp2(word, root->value);
        int my_val_len = strlen(root->value);
        char *suffix;
        trienode * newchild;

        if(match_index == STRCMP_NO_MATCH){
                return FAILURE;
        }
        else if(match_index == STRCMP_EXACT_MATCH){
                return SUCCESS;
        }
        else{
                //Check if I am a complete prefix
                if(match_index == my_val_len -1 ){
                        children = trie_get_children(root);
                        for(i = 0; i < trie_num_children(root); i++){
                                if( _insert_word_recur( (trienode *)children[i], 
                                                        word + my_val_len, wlen - my_val_len)){
                                        return SUCCESS;
                                }
                        }
                        trie_add_child( root, 
                                        trie_createnode (word + my_val_len, wlen - my_val_len));
                        return SUCCESS;
                }
                //Split myself
                else {
                        suffix = strsplit(&(root->value), match_index + 1);
                        //create a new child with the suffix
                        newchild = trie_createnode(suffix, strlen(suffix));
                        children = trie_get_children(root);
                        for(i = 0; i < trie_num_children(root); i++){
                                //remove the child from root and attach to new child
                                trie_remove_child       (root,     (trienode *)children[i]);
                                trie_add_child          (newchild, (trienode *)children[i]);
                        }
                        trie_add_child (root, newchild);
                        //Add the unmatching suffix of the input word as a new child
                        if(match_index == wlen - 1){
                                //The new split root is a word
                                root->is_word = TRUE;
                        }
                        else{
                                root->is_word = FALSE;
                                trie_add_child (root,
                                               trie_createnode(word + match_index +1, wlen - match_index -1));
                        }
                        return SUCCESS;

                }
        }
        return FAILURE;
}

/*
 * Insert a word into the dictionary
 */
bool insert(dict * dictionary, char *word, int wlen){

        if(dictionary == NULL || word == NULL || wlen <= 0){
                return FAILURE;
        }

        void ** roots = trie_get_children(dictionary->root);
        int num_children = trie_num_children(dictionary->root);
        int i = 0;

        for( i=0; i< num_children; i++){
                if(_insert_word_recur( (trienode *)roots[i],
                                        word, wlen)){
                        return SUCCESS;
                }
        }

        trie_add_child(dictionary->root, 
                        trie_createnode(word, wlen));
        return SUCCESS;
        
}

void _print_words_recur( trienode * root, int indent){
        if(root == NULL)
                return;
        int i = 0;
        void ** children = trie_get_children(root);
        int num_children = trie_num_children(root);

        for (i = 0; i< indent-1; i++){
                printf("|       ");
        }
        printf("|-------");
        if(root->is_word){
                printf("$%s#$ %d\n", root->value, root->num_strings );
        }
        else{
                printf("$%s$ %d\n", root->value, root->num_strings );
        }

        for( i=0; i< num_children; i++){
                _print_words_recur( (trienode *)children[i], indent + 1);
        }

        return;
}

/*
 * Print the words in the dictionary as a tree
 */
void print (dict *dictionary){
        if(dictionary == NULL){
                return;
        }
        int i = 0;
        int indent = 0;

        word_count(dictionary);

        void ** roots = trie_get_children(dictionary->root);
        int num_children = trie_num_children(dictionary->root);

        printf("ROOT %d\n", dictionary->root->num_strings);

        for( i=0; i< num_children; i++){
                _print_words_recur( (trienode *)roots[i], indent + 1);
                
        }
        return;
}

/*
 * Recursively populate number of valid strings in the sub tree
 */

int _num_strings_in_subtree_recur(trienode *root){
        if(root == NULL){
                return FAILURE;
        }
        int i = 0;
        void ** children = trie_get_children(root);
        int count = 0;

        for( i=0; i< trie_num_children(root); i++){
                count += _num_strings_in_subtree_recur( (trienode *)children[i]);
        }

        if(root->is_word ){
                root->num_strings = count +1;
        }
        else{
                root->num_strings = count;
        }
        return root->num_strings;
}

int word_count(dict *dictionary){

        int i;
        void ** roots = trie_get_children(dictionary->root);
        int count = 0;

        for( i=0; i< trie_num_children(dictionary->root) ; i++){
               count +=  _num_strings_in_subtree_recur( (trienode *)roots[i]);
                
        }
        return (dictionary->root->num_strings = count);
}
bool _find_recur(trienode * root, char *s, lookup * result){

        int i;
        void ** children ;
        int match_index = strcmp2(root->value, s);
        if(match_index == STRCMP_EXACT_MATCH){
                if(root->is_word)
                        return SUCCESS;
                else
                        return FAILURE;
        }
        else if (match_index == STRCMP_NO_MATCH){
                return FAILURE;
        }
        else{
                if(match_index == strlen(root->value) -1){
                        children = trie_get_children(root);

                        for (i=0; i< trie_num_children(root); i++){
                                if(_find_recur((trienode *)children[i], s+match_index+1, result)){
                                        return SUCCESS;
                                }
                        }
                }
        }
        return FAILURE;

}

bool find (dict * dictionary, char * s){
        if(dictionary == NULL || s == NULL){
                return FAILURE;
        }
        
        int i;
        void ** roots = trie_get_children(dictionary->root);
        int num_children = trie_num_children(dictionary->root);

        for( i=0; i<num_children; i++){
                if(_find_recur((trienode *)roots[i], s, NULL)){
                        return SUCCESS;
                }
        }
        return FAILURE;
}


