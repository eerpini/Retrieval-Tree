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
        i++;
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
/*
 * A String split function, creates two new strings
 * the prefix is still at str but with pref_len 
 * the second half is returned
 * all strings are null terminated
 */
char * strsplit (char **str, int pref_len){
    int curr_len = strlen(*str);

    char * prefix = malloc (sizeof(char) * (pref_len + 1));
    char * suffix = malloc (sizeof(char) * (curr_len - pref_len + 1));

    strncpy(prefix, *str, pref_len);
    prefix[pref_len] = 0;

    strncpy(suffix, (*str)+pref_len, curr_len - pref_len);
    suffix[curr_len - pref_len] = 0;

    free(*str);
    *str = prefix;

    return suffix;

}
/*
 * Joins the two strings and puts the result in the first one
 * To avoid possible out of bounds access, we free the old copy of s1
 * and assign the newly allocated copy to it
 * Also returns a pointer to the concatenated string which is the same as *s1
 */

char * strjoin (char **s1, char *s2){
    if(s1 == NULL || s2 == NULL){
        return NULL;
    }

    char *s = malloc(sizeof(char) * (strlen(*s1) + strlen(s2) + 1));

    strcpy(s, *s1);
    strcpy(s+strlen(*s1), s2);

    free(*s1);
    *s1 = s;
    return s;
}
