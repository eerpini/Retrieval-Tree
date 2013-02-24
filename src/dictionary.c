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
bool _find_recur(trienode * root, char *s){

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
                                if(_find_recur((trienode *)children[i], s+match_index+1)){
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
                if(_find_recur((trienode *)roots[i], s)){
                        return SUCCESS;
                }
        }
        return FAILURE;
}

void _fill_strings_recur (trienode * root, void ** strings, int len){

        int i;
        void **children ;
        int running_count = 0;

        for( i=0; i < len; i++){
                strcpy((char *)strings[i] + strlen((char*)strings[i]), root->value);
        }
        children  = trie_get_children(root);
        if(children == NULL){
                return;
        }

        if(root->is_word && root->num_strings > 1){
                running_count++;
        }

        for(i=0; i < trie_num_children(root); i++){
                _fill_strings_recur( (trienode *)children[i], (void **)(strings + running_count), ((trienode *)children[i])->num_strings);
                running_count +=((trienode *) children[i])->num_strings;
        }

        return;
}

void _pfind_recur(trienode * root, char *s, int s_start, lookup * result){
        int i;
        void ** children ;
        int match_index = strcmp2(root->value, s+s_start);
        int running_count = 0;
        if(match_index == STRCMP_EXACT_MATCH){
                //Populate string counts and return if 0
                if(_num_strings_in_subtree_recur(root) == 0){
                        return;
                }
                
                //Allocate memory for the prefixes
                result->matches = (void **)malloc(sizeof(char *) * root->num_strings);
                result->len = root->num_strings;
                //Append whole string so far
                for(i=0; i< root->num_strings; i++){
                        result->matches[i] = (void *)malloc(sizeof(char) *MAX_WORD_SIZE);
                        strcpy(result->matches[i], s);
                }

                children  = trie_get_children(root);
                if(root->is_word && root->num_strings > 1){
                        running_count++;
                }
                for(i=0; i < trie_num_children(root); i++){
                        _fill_strings_recur( (trienode *)children[i], (void **)(result->matches + running_count), ((trienode *)children[i])->num_strings);
                        running_count += ((trienode *)children[i])->num_strings;
                }
        }
        else if (match_index == STRCMP_NO_MATCH){
                log("No match found for %s at node %s\n", s+s_start, root->value);
                return;
        }
        else{
                log("LOG1 match index is [%d] and s_start is [%d] and strlen(s) is [%d] \n"
                                ,match_index, s_start, strlen(s));
                if(match_index == strlen(root->value) -1){
                        log("LOG1");
                        children = trie_get_children(root);

                        for (i=0; i< trie_num_children(root); i++){
                                _pfind_recur((trienode *)children[i], s, match_index+1, result);
                                        return ;
                        }
                        return;
                }
                else if(match_index +1  == strlen(s) - s_start){
                        log("LOG2");
                        //if the passed prefix from above was a prefix of root->value
                         //Populate string counts and return if 0
                        if(_num_strings_in_subtree_recur(root) == 0){
                                return;
                        }
                        
                        //Allocate memory for the prefixes
                        result->matches = (void **)malloc(sizeof(char *) * root->num_strings);
                        result->len = root->num_strings;
                        //Append whole string so far
                        for(i=0; i< root->num_strings; i++){
                                result->matches[i] = (void *)malloc(sizeof(char) *MAX_WORD_SIZE);
                                //Copy part of s and root->value
                                strncpy(result->matches[i], s, s_start);
                                strcpy((char *)result->matches[i] + s_start, root->value);
                        }

                        children  = trie_get_children(root);
                        if(root->is_word && root->num_strings > 1){
                                running_count++;
                        }
                        for(i=0; i < trie_num_children(root); i++){
                                _fill_strings_recur( (trienode *)children[i], (void **)(result->matches + running_count), ((trienode *)children[i])->num_strings);
                                running_count += ((trienode *)children[i])->num_strings;
                        }

                }
        }
        return;

}

lookup * pfind( dict *dictionary, char *s){
        if(dictionary == NULL || s == NULL){
                return FAILURE;
        }
        
        int i;
        void ** roots = trie_get_children(dictionary->root);
        int num_children = trie_num_children(dictionary->root);
        lookup * temp = malloc(sizeof(lookup));
        temp->len = 0;
        temp->matches = NULL;

        for( i=0; i<num_children; i++){
                _pfind_recur((trienode *)roots[i], s, 0, temp);
                if(temp->len > 0){
                        return temp;
                }
        }
        return temp;
}

bool _remove_recur(trienode * root, char *s, trienode **child_to_rm){

        int i;
        void ** children ;
        int match_index = strcmp2(root->value, s);
        if(match_index == STRCMP_EXACT_MATCH){
                if(root->is_word){
                        root->is_word = FALSE;
                        //Mark the current node for removal if it has no children
                        if(trie_num_children(root) == 0){
                                log("Exact match found, setting myself here");
                                *child_to_rm = root;
                        }
                        else{
                                *child_to_rm = NULL;
                        }
                        return SUCCESS;
                }
                else{
                        return FAILURE;
                }
        }
        else if (match_index == STRCMP_NO_MATCH){
                return FAILURE;
        }
        else{
                if(match_index == strlen(root->value) -1){
                        children = trie_get_children(root);

                        for (i=0; i< trie_num_children(root); i++){
                                log("Passing on to the next level with [%s] I have [%s]\n", s+match_index+1, root->value);
                                if(_remove_recur((trienode *)children[i], s+match_index+1, child_to_rm)){
                                        if(*child_to_rm != NULL){
                                                trie_remove_child(root, *child_to_rm);
                                                trie_freenode(*child_to_rm);
                                                *child_to_rm = NULL;

                                                //Reconcile if only one child is remaining
                                                if(trie_num_children(root) == 1){
                                                        //There is only one child anyway
                                                        trienode * merge_child = (trie_get_children(root))[0];
                                                        void ** moving_children = trie_get_children(merge_child);
                                                        int merge_num = trie_num_children(merge_child);
                                                        int j;
                                                        for(j=0; j < merge_num; j++){
                                                                trie_remove_child(merge_child, moving_children[i]);
                                                                trie_add_child(root, moving_children[i]);
                                                        }
                                                        //Concatenate strings
                                                        strjoin(&(root->value), merge_child->value);
                                                        root->is_word = merge_child->is_word;
                                                        trie_remove_child(root, merge_child);
                                                        trie_freenode(merge_child);
                                                }
                                        }
                                        else{
                                                log("Got succces with [%s] but did not have to do anything\n", root->value);
                                        }
                                        return SUCCESS;
                                }
                        }
                }
        }
        return FAILURE;
}

bool remove_word ( dict *dictionary, char *s){
        if(dictionary == NULL || s == NULL){
                return FAILURE;
        }

        trienode * temp;
        int i;
        void ** roots = trie_get_children(dictionary->root);
        int num_children = trie_num_children(dictionary->root);

        for( i=0; i<num_children; i++){
                if(_remove_recur((trienode *)roots[i], s, &temp) ){
                        if(temp != NULL && temp == roots[i]){
                                trie_remove_child(dictionary->root, temp);
                                log("Removing the child here");
                                trie_freenode(temp);
                        }
                        return SUCCESS;
                }
        }
        return FAILURE; 

}
       
