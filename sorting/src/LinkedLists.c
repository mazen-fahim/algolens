#include <stdio.h>
#include <stdlib.h>
#include "../include/LinkedList.h"

void list_init (List *list, void (*destroy)(void *data))
{
    list->destroy = destroy;
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    return;
}
void list_destroy(List *list)
{
    void *data;
    while(list_size(list) > 0)
    {
        if(list_rem_next(list, NULL, &data)  == 0 && list->destroy != NULL)
            list->destroy(data);
    }
    return;
}
int list_ins_next(List *list, List_elmt *element, const void *data)
{
    List_elmt *new_element;
    if((new_element = (List_elmt *) malloc(sizeof(List_elmt))) == NULL)
        return -1;
    new_element->data = (void *)data;
    //insert as head
    if(element == NULL)
    {
        if(list_size(list) == 0)
            list->tail = new_element;

        new_element->next = list->head;
        list->head = new_element;
    }
    else 
    {
        if(element->next == NULL)
            list->tail = new_element;
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}
// here we pass a pointer to a pointer so that the function can modify a pointer in the caller function. so we have to pass the pointer by reference.
// it returns a pointer pointing to the data removed so that we can pass it to the user define destroy function.
int list_rem_next(List *list, List_elmt *element, void **data)
{
    List_elmt *old_element;
    //don't allow removal of empty list
    if(list_size(list) == 0)
        return -1;
    //remove from head
    if(element == NULL)
    {
        //store the adress of the element being removed in old_element to call free on it. DON'T LOSE IT!
        old_element = list->head;
        list->head = list->head->next;
        if(list_size(list) == 1)
            list->tail = NULL;
    }
    else 
    {
        //return error if removing from tail node
        if(element->next == NULL)
            return -1;
        //set the data pointer to point to the data being removed
        *data = element->next->data;
        //store the adress of the element being removed in old_element to call free on it. DON'T LOSE IT!
        old_element = element->next;
        element->next = element->next->next;
        //now that i have removed the old_element i have to check if the element became the tail node
        if(element->next == NULL)
            list->tail = element;
    }
    free(old_element);
    list->size--;
    return 0;
}

int list_get_element_at_index(List *list, List_elmt **target, int index)
{
    if(list->size == 0)
        return -1;
    else 
    {
        *target = list->head;
        for(int i = 0; i < index; i++)
            *target = (*target)->next;
        return 0;
    }
}

