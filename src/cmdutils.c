/*
 * @satish
 * Sun Feb 24 00:11:31 PST 2013
 */
#include "cmdutils.h"

//_cmd is always null terminated
char _cmd [CMD_LINE_MAX + 1];
int _cmd_len = 0;

/*
 * Split the string in _cmd into "<dictionary operation> text to insert"
 * Copy the text to be inserted into word and return the operation found
 */
DICT_OP parse_input(char *word, int *len){

    if(word == NULL){
        return DICT_INVALID_OP;
    }

    int i= 0;

    if(strncmp(_cmd, DICT_PRINTT_CMD, 6) == 0){
        return DICT_PRINTT_OP;
    }

    for(i = 0; i < _cmd_len; i++){
        if(_cmd[i] == ' ')
            break;
    }
    //For now since all operations are six chars long
    if( i != 6 ){
        return DICT_INVALID_OP;
    }

    if( _cmd[i+1] == 0){
        return DICT_INVALID_OP;
    }

    if(strncmp(_cmd, DICT_INSERT_CMD, 6) == 0){
        strncpy(word, _cmd + 7, _cmd_len - 7);
        *len = _cmd_len - 7;
        return DICT_INSERT_OP;
    }
    if(strncmp(_cmd, DICT_LOOKUP_CMD, 6) == 0){
        strncpy(word, _cmd + 7, _cmd_len - 7);
        *len = _cmd_len - 7;
        return DICT_LOOKUP_OP;
    }
    if(strncmp(_cmd, DICT_PREFIX_CMD, 6) == 0){
        strncpy(word, _cmd + 7, _cmd_len - 7);
        *len = _cmd_len - 7;
        return DICT_PREFIX_OP;
    }
    if(strncmp(_cmd, DICT_REMOVE_CMD, 6) == 0){
        strncpy(word, _cmd + 7, _cmd_len - 7);
        *len = _cmd_len - 7;
        return DICT_REMOVE_OP;
    }

    return DICT_INVALID_OP;
}

/*
 * Read one line from the stdin and put it in _cmd, put the length in _cmd_len (including null character)
 * returns the number of characters read
 */
int readline(){
    char ch = 0;
    int i = 0;
    for(;;) {
        ch = getchar();
        if(ch == EOF){
            return 0;
        }
        if(ch == '\n'){
            break;
        }
        _cmd[i++] = ch;
    }
    _cmd[i++] = 0;
    log("The length of the _cmd [%s] is %d and I am putting %d\n",
            _cmd, strlen(_cmd), i);
    _cmd_len = i;
    return i>0 ?i-1 :0 ;
}
