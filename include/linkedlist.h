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

void _free_node(ll_node *, bool);
ll* ll_create();
void ll_free(ll *);
void ll_add(ll *, void *);
int ll_remove(ll *, void *, bool);
void ** ll_get_nodes(ll *);
int ll_length(ll *);

#endif
