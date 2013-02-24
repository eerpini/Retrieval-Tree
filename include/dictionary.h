#include "commondefs.h"
#include "cmdutils.h"

#ifndef DICTIONARY_SEEN
#define DICTIONARY_SEEN

#define MAX_WORD_SIZE 1024 - CMD_LINE_MAX -1 

int get_dict_string_count();
int string_count_recur(trienode *);
void dict_print_words();
void print_words_recur();



#endif
