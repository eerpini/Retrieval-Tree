#include <dictionary.h>
#include <cmdutils.h>
#include <strutils.h>



int main(int argc, char **argv){

        char *input_word = malloc( sizeof(char ) * (MAX_WORD_SIZE + 1)); 
        while(readline() > 0){
                switch(parse_input(input_word)){

                        case DICT_INSERT_OP:
                                printf("Dictionary insert operation found with word : %s\n", input_word);
                                break;
                        case DICT_LOOKUP_OP:
                                printf("Dictionary lookup operation found with word : %s\n", input_word);
                                break;
                        case DICT_PREFIX_OP:
                                printf("Dictionary prefix operation found with word : %s\n", input_word);
                                break;
                        case DICT_REMOVE_OP:
                                printf("Dictionary remove operation found with word : %s\n", input_word);
                                break;
                        case DICT_INVALID_OP:
                                printf("Dictionary invalid operation found\n");
                                break;
                        default:
                                printf("parse_input returned invalid code\n");
                }
        }

        return EXIT_SUCCESS;
}
