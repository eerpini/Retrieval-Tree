/*
 * @satish 
 * Sat Feb 23 23:27:34 PST 2013
 */

#include "strutils.h"
#include "commondefs.h"
/*
 * If s1 and s2 are exactly equals returns 0
 * Return i where i is the highest matching index and i < len(s1) and i < len(s2) 
 * Return -1 if no match was found at all
 */
int strcmp2(char *s1, char *s2){
        if(s1 == NULL || s2 == NULL){
                return STRCMP_NO_MATCH;
        }
        int len1 = strlen(s1);
        int len2 = strlen(s2);
        int i = 0;
        while(i < len1 && i < len2){
                if(s1[i] != s2[i]){
                        break;
                }
        }

        //No matching character
        if(i == 0){
                return STRCMP_NO_MATCH;
        }
        //Lens are equal and all match
        if(i == len1 && i == len2){
                return STRCMP_EXACT_MATCH;
        }
        //Partial match
        return i-1;

}

        


