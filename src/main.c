#include <unistd.h>
#include <dictionary.h>

int main(int argc, char **argv){

        char *input_word = malloc( sizeof(char ) * (MAX_WORD_SIZE + 1)); 
        dict *mydict = new_dictionary();
        log("The limits of the allocated word are %p %p MAX_WORD_SIZE is %d\n", input_word, input_word + MAX_WORD_SIZE + 1, MAX_WORD_SIZE);
        int len = 0;
        int i;
        if(isatty(fileno(stdin))){
                printf("> ");
        }
        while(readline() > 0){
                log("The value of num_strings for root at %p is %d\n", mydict->root, mydict->root->num_strings);
                switch(parse_input(input_word, &len)){

                        case DICT_INSERT_OP:
                                log("Dictionary insert operation found with word : %s\n", input_word);
                                log("The value of num_strings for root at %p is %d\n", mydict->root, mydict->root->num_strings);
                                insert(mydict, input_word, len-1);
                                break;
                        case DICT_LOOKUP_OP:
                                log("Dictionary lookup operation found with word : %s\n", input_word);
                                if(find(mydict, input_word)){
                                        printf("[%s] is present\n", input_word);
                                }
                                else{
                                        printf("[%s] not found\n", input_word);
                                }
                                break;
                        case DICT_PREFIX_OP:
                                log("Dictionary prefix operation found with word : %s\n", input_word);
                                lookup *  result = pfind(mydict, input_word);
                                if(result->len > 0){
                                        for(i = 0; i< result->len; i++){
                                                printf("[%s] matches [%s]\n", result->matches[i], input_word);
                                        }
                                }
                                else{
                                        printf("No matches found");
                                }
                                break;
                        case DICT_REMOVE_OP:
                                log("Dictionary remove operation found with word : %s\n", input_word);
                                break;
                        case DICT_PRINTT_OP:
                                log("Dictionary printt operation found with word : %s\n", input_word);
                                print(mydict);
                                break;
                        case DICT_INVALID_OP:
                                log("Dictionary invalid operation found\n");
                                break;
                        default:
                                log("parse_input returned invalid code\n");
                }
                if(isatty(fileno(stdin))){
                        printf("> ");
                }
        }

        return EXIT_SUCCESS;
}
