#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>


#ifndef COMMONDEFS_SEEN
#define COMMONDEFS_SEEN
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define FAILURE 0
typedef char bool;

void nullprint(char *, ...);

//DEBUGGING
#ifdef DEBUG
#define log printf
#else
#define log nullprint
#endif
#endif
