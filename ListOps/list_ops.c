#include "list_ops.h"
#include <string.h>
#include <stdio.h>

/*
typedef struct {
   size_t length;
   list_element_t elements[];
} list_t;
*/
// constructs a new list
list_t *new_list(size_t length, list_element_t elements[])
{
    list_t *new_list = malloc(sizeof(size_t) + sizeof(list_element_t) * length);
    if (new_list != NULL) {
        new_list->length = length;
        if (elements != NULL) {
            memcpy(new_list->elements, elements, sizeof(*elements) * length);
        }
    }
    return new_list;
}

// append entries to a list and return the new list
list_t *append_list(list_t *list1, list_t *list2)
{
    list_element_t new_elements[list1->length + list2->length];
    for (size_t i = 0; i < list1->length; i++)
        new_elements[i] = list1->elements[i];
    for (size_t i = 0; i < list2->length; i++)
        new_elements[list1->length + i] = list2->elements[i];
    /*
    memcpy(new_elements,list1->elements,list1->length);
    memcpy(&new_elements[list1->length],list2->elements,list2->length);
    */
    return new_list(list1->length + list2->length, new_elements);
}

 /*
// filter list returning only values that satisfy the filter function
list_t *filter_list(list_t *list, bool (*filter)(list_element_t))
{
    return NULL;
}

// returns the length of the list
size_t length_list(list_t *list)
{
    return 0;
}

// return a list of elements whose values equal the list value transformed by
// the mapping function
list_t *map_list(list_t *list, list_element_t (*map)(list_element_t))
{
    return NULL;
}

// folds (reduces) the given list from the left with a function
list_element_t foldl_list(list_t *list, list_element_t initial,
                          list_element_t (*foldl)(list_element_t,
                                                  list_element_t))
{
    return (list_element_t*)NULL;
}

// folds (reduces) the given list from the right with a function
list_element_t foldr_list(list_t *list, list_element_t initial,
                          list_element_t (*foldr)(list_element_t,
                                                  list_element_t))
{
    return NULL;
}

// reverse the elements of the list
list_t *reverse_list(list_t *list)
{
    return NULL;
}

// destroy the entire list
// list will be a dangling pointer after calling this method on it
void delete_list(list_t *list)
{
    return;
}

*/

/**
 * ------------------------------
*/

void printList(list_t* l)
{
    if(l != NULL) {
        printf("\n- - - - - - - - - -\n");
        printf("lenght  : %zu\n",l->length);
        printf("elements: [");
        for(int i = 0; i < l->length; i++){
            printf("%u",l->elements[i]);
            if((l->length-i-1) > 0){
                printf(",");
            }
        }
    }
    printf("]\n");
}

int main ()
{
    list_t *l, *l1, *l2;
    list_element_t lst1[3] = {1,2,3};
    list_element_t lst2[4] = {4,3,2,1};
    l1 = new_list(sizeof(lst1)/sizeof(lst1[0]), lst1);
    printList(l1);
    l2 = new_list(sizeof(lst2)/sizeof(lst2[0]), lst2);
    printList(l2);
    l = append_list(l1,l2);
    printList(l);
}