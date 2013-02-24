#include "linkedlist.h"

void free_node (ll_node * node){
        if(node == NULL){
                return;
        }
        if(node->data != NULL){
                free(node->data);
        }
        printf("FREEING THE NODE ATTEMPTED");
        free(node);
        printf("FREEING THE NODE SUCCESSFUL");
        return;
}

ll* create_ll (){

        ll * temp = malloc(sizeof(ll));
        temp->head = temp->tail = NULL;
        temp->len = 0;

        return temp;
}

void free_ll (ll * list){
        if(list == NULL){
                return;
        }
        ll_node * temp = list->head;
        ll_node * next = temp;
        while(temp != NULL){
                next = temp->next;
                free_node(temp);
                temp = next;
        }
        free(list);
        return;
}

void add(ll * list, void *data){

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
        
int remove(ll * list , void *data){

        if(list->head == NULL){
                return -1;
        }

        ll_node *temp = NULL;
        ll_node *prev = NULL;

        if(list->head == list->tail){
                //This is a pointer comparison, this is DANGEROUS
                if(list->head->data == data){
                        temp = list->head;
                        list->head = list->tail = NULL;
                        free_node(temp);
                        list->len--;
                        return 0;

                }
                return -1;
        }

        temp = list->head;
        prev = temp;
        while(temp->data != data && temp != NULL){
                temp = temp->next;
                prev = temp;
        }

        if(temp == NULL){
                return -1;
        }

        if(temp == list->head){
                list->head = list->head->next;
                free_node(temp);
                list->len--;
                return 0;
        }

        if(temp == list->tail){
                list->tail = prev;
                list->tail->next = NULL;
                free_node(temp);
                list->len--;
                return 0;
        }

        prev->next = temp->next;
        free_node(temp);
        list->len--;
        return 0;
}

void ** get_nodes (ll *list){
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

