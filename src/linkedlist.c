#include <linkedlist.h>

void _free_node (ll_node * node, bool FREE_DATA){
        if(node == NULL){
                return;
        }
        if(node->data != NULL && FREE_DATA){
                free(node->data);
        }
        free(node);
        return;
}

ll* ll_create (){

        ll * temp = malloc(sizeof(ll));
        temp->head = temp->tail = NULL;
        temp->len = 0;

        return temp;
}

void ll_free (ll * list){
        if(list == NULL){
                return;
        }
        ll_node * temp = list->head;
        ll_node * next = temp;
        while(temp != NULL){
                next = temp->next;
                _free_node(temp, TRUE);
                temp = next;
        }
        free(list);
        return;
}

void ll_add(ll * list, void *data){

        ll_node *new_node  = malloc(sizeof(ll_node));
        new_node->data = data;
        new_node->next = NULL;

        if(list->head == NULL){
                list->head = new_node;
                list->tail = list->head;
                list->len = 1;
                return;
        }

        list->tail->next = new_node;
        list->tail = new_node;
        list->len++;

        return;
}
        
int ll_remove(ll * list , void *data, bool FREE_DATA){

        if(list == NULL || list->head == NULL || data == NULL){
                return FAILURE;
        }

        ll_node *temp = NULL;
        ll_node *prev = NULL;

        if(list->head == list->tail){
                //This is a pointer comparison, this is DANGEROUS
                if(list->head->data == data){
                        temp = list->head;
                        list->head = list->tail = NULL;
                        _free_node(temp, FREE_DATA);
                        list->len--;
                        return SUCCESS;

                }
                return -1;
        }

        temp = list->head;
        prev = temp;
        while(temp->data != data && temp != NULL){
                prev = temp;
                temp = temp->next;
        }

        if(temp == NULL){
                return FAILURE;
        }

        if(temp == list->head){
                list->head = list->head->next;
                _free_node(temp, FREE_DATA);
                list->len--;
                return SUCCESS;
        }

        if(temp == list->tail){
                list->tail = prev;
                list->tail->next = NULL;
                _free_node(temp, FREE_DATA);
                list->len--;
                return SUCCESS;
        }

        prev->next = temp->next;
        _free_node(temp, FREE_DATA);
        list->len--;
        return SUCCESS;
}

void ** ll_get_nodes (ll *list){
        if(list->head == NULL){
                return NULL;
        }

        char ** return_set = (char **)malloc(sizeof(char *) * list->len);
        int i = 0;
        ll_node * temp = list->head;
        while(temp!=NULL){
                return_set[i++] = (char *)temp->data;
                temp=temp->next;
        }
        return (void **)(return_set);
}

int ll_length(ll *list){
        if(list == NULL){
                return FAILURE;
        }
        return list->len;
}
