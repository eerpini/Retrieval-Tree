#include <commondefs.h>

void nullprint (char *s, ...){

        return ;

}

void xfree (void * ptr){
	if(ptr != NULL){
		free(ptr);
	}
	return;
}
