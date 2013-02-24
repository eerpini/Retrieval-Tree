/*
 * Definitions and constants for cmdutils.h
 */
#ifndef CMDUTILS_SEEN
#define CMDUTILS_SEEN 
#include "commondefs.h"

#define CMD_LINE_MAX 1024
extern char  _cmd[];
extern int _cmd_len;

#define DICT_INSERT_CMD "insert"
#define DICT_LOOKUP_CMD "lookup"
#define DICT_PREFIX_CMD "prefix"
#define DICT_REMOVE_CMD "remove"
#define DICT_PRINTT_CMD "printt"
#define DICT_EXPORT_CMD "export"

//Insert word into the dictionary
#define DICT_INSERT_OP 107
//Lookup the word in the dictionary
#define DICT_LOOKUP_OP 108
//Prefix lookup the word in the dictionary
#define DICT_PREFIX_OP 109
//Remove word from the dictionary
#define DICT_REMOVE_OP 110
//Print the words in the dictionary as a tree
#define DICT_PRINTT_OP 111
//Export the contents of the dictionary into a text file
#define DICT_EXPORT_OP 112
//Invalid dictionary operation
#define DICT_INVALID_OP 117

typedef int DICT_OP;


DICT_OP parse_input(char *, int *);
int readline();

#endif
