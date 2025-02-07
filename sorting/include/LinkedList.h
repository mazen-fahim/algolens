#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct List_elmt
{
    void *data;
    void *key;
    struct List_elmt *next;

}List_elmt;

typedef struct List
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    List_elmt *head;
    List_elmt *tail;

}List;

void list_init (List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_get_element_at_index(List *list, List_elmt **target, int index);
int list_ins_next(List *list, List_elmt *element, const void *data);
int list_rem_next(List *list, List_elmt *element, void **data);

#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head? 1 : 0)
#define list_is_tail(list, element) ((element) == (list)->tail? 1 : 0)
#define list_data(element) ((element)-> data)
#define list_next(element) ((element)->next)


#endif
