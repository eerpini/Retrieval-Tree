#include <commondefs.h>

#ifndef LINKEDLIST_SEEN
#define LINKEDLIST_SEEN


typedef struct list_node {
        void *data;
        struct list_node *next;
}ll_node;

typedef struct linkedlist{
        ll_node * head;
        ll_node * tail;
        int len;
}ll;

void free_node(ll_node *);
ll* create_ll ();
void free_ll (ll *);
void add(ll *, void *);
int remove(ll *, void *);
void ** get_nodes(ll *);

#endif
