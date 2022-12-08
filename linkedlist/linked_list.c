#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_node {
   struct list_node *prev, *next;
   ll_data_t data;
};

struct list {
   struct list_node *first, *last;
};

// constructs a new (empty) list
struct list *list_create(void)
{
    struct list* l = malloc(sizeof(struct list));
    if(l != NULL){
        l->first = NULL;
        l->last = NULL;
    }
    return l;
}

// counts the items on a list
size_t list_count(const struct list *list)
{
    struct list_node *p = list->first;
    int count = 0;
    while(p != NULL){
        count++;
        p = p->next;
    }
    return count;
}

// inserts item at back of a list
void list_push(struct list *list, ll_data_t item_data)
{
    struct list_node* node = malloc(sizeof(struct list_node));
    if(node != NULL){
        node->data = item_data;
        node->prev = list->last;
        node-> next = NULL;
        if(list->last != NULL){//list not empty
            struct list_node* old_last = list->last;
            old_last->next = node;
        }
        list->last = node;
        if(list->first == NULL){ //empry list
            list->first = node;
        }
    }
    return;
}

// removes item from back of a list
ll_data_t list_pop(struct list *list)
{
    ll_data_t d;
    struct list_node *last_node = list->last;
    //struct list_node *end= last_node->prev;
    
    d = (ll_data_t)last_node->data;
    //list with only one item (first == last)
    if(list->first == list->last){
        //empty list -> NULL
        list->first = NULL;
        list->last = NULL;
    } else {
        //remove reference to last node
        list->last = last_node->prev;
        //correct last node
        list->last->next = NULL;
    }
    free(last_node);
    return d;
}

// inserts item at front of a list
void list_unshift(struct list *list, ll_data_t item_data)
{
    struct list_node *new_node = calloc(1,sizeof(struct list_node));
    if(new_node != NULL){
        new_node->data = item_data;
        new_node->prev = NULL;
        new_node->next = list->first;
        list->first = new_node;
    }
    return;
}

// removes item from front of a list
ll_data_t list_shift(struct list *list)
{
    ll_data_t data = 0;
    //if list is empty : return 0;
    if(list->first == NULL && list->last == NULL){
        return data;
    }
    //list has one or more itens
    if(list->first != NULL){
        struct list_node* n = list->first;
        data = n->data;
        list->first = n->next;
        if(n->next != NULL){
            n->next->prev = NULL;
        }
        free(n);
    }
    return data;
}

// deletes a node that holds the matching data
void list_delete(struct list *list, ll_data_t data)
{
    struct list_node *p = list->first;
    struct list_node *found = NULL;

    while(p != NULL){
        if(p->data == data){
            found = p;
            break;
        }
        p = p->next;
    }
    if(found != NULL){
        //remove node "found"
        struct list_node *prv = found->prev;
        struct list_node *nxt = found->next;
        if(prv != NULL && nxt != NULL){
            //middle
            prv->next = nxt;
            nxt->prev = prv;
        } else{
            //first
            if(prv == NULL){
                list->first = nxt;
                if(nxt != NULL && nxt->prev != NULL){
                    nxt->prev = NULL;
                }               
            }
            //last
            if(nxt == NULL){
                list->last = prv;
                if(prv != NULL && prv->next != NULL){
                    prv->next = NULL;
                }
            }
        }
    }
    return;
}

// destroys an entire list
// list will be a dangling pointer after calling this method on it
void list_destroy(struct list *list)
{
    list->first = NULL;
    list->last = NULL;
}

/* - - - - - - */
void print_list(struct list* lst){
    //show list
    printf(" -  -  -  -  -  -  -  -\n");
    if(lst != NULL){
        printf(" addr :  %p\n",(void*)lst);
        printf(" first:  %p\n",(void*)lst->first);
        printf(" last :  %p\n",(void*)lst->last);
    } else {
        printf("list is NULL!\n");
        return;
    }
    //iterate over list (not NULL)
    int num = 0;
    struct list_node* node = lst->first;
    while(node != NULL){
        //show
        printf("node %3i", num);
        printf("     addr :  %p\n",(void*)node);
        printf("     prev :  %p\n",(void*)node->prev);
        printf("     next :  %p\n",(void*)node->next);
        printf("     data :  %i\n",(int)node->data);
        //increment
        num++;
        node = node->next;
    }
}

int
main()
{
    //create
    struct list* list = list_create();
    print_list(list);
    //push
    list_push(list, 7);
    print_list(list);
    //push
    list_push(list, 2);
    print_list(list);
    //pop
    int last = list_pop(list);
    printf("pop: %i(%i)\n",last,2);
    print_list(list);
    //pop
    last = list_pop(list);
    printf("pop: %i(%i)\n",last,7);
    print_list(list);
    //push
    list_push(list, 1);
    list_push(list, 2);
    print_list(list);
    //shift
    last = list_shift(list);
    printf("shift: %i(%i)\n",last,1);
    print_list(list);
    //delete
    list_delete(list, 4);
    print_list(list);
    //destroy
    list_destroy(list);
}