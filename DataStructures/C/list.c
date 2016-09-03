// list.c
//Refer:算法精解：C语言描述 (美)Kyle Loudon (作者), 肖翔 (译者), 陈舸 (译者)
//通过编译，未测试
#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List *list, void (*destroy)(void *data))
{
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;
}

void list_destroy(List *list)
{
    void * data;
    while (list_size(list) > 0)
    {
        if (list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL)
            list->destroy(data);
    }
    memset(list, 0, sizeof(list));
    return;
}

//如果element设置为NULL，则新元素插入链表头部。
int list_ins_next(List *list, ListElmt *element, const void *data)
{
    ListElmt *new_element;
    if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
        return -1;
    new_element->data = (void *)data;
    if (element == NULL)
    {
        if (list_size(list) == 0)
            list->tail = new_element;
        new_element->next = list->head;
        list->head = new_element;
    }
    else
    {
        if (element->next == NULL)
            list->tail = new_element;
        new_element->next = element->next;
        element->next = new_element;
    }
    list->size++;
    return 0;
}

//如果element设置为NULL，则移除链表头元素。
int list_rem_next(List *list, ListElmt *element, void **data)
{
    ListElmt * old_element;
    if (list_size(list) == 0)
        return -1;
    if (element == NULL)
    {
        *data = list->head->data;
        old_element = list->head;
        list->head = list->head->next;
        if (list_size(list) == 1)
            list->tail = NULL;
    }
    else
    {
        if (element->next == NULL)
            return -1;
        *data = element->next->data;
        old_element = element->next;
        element->next = element->next->next;
        if (element->next == NULL)
            list->tail = element;
    }
    free(old_element);
    list->size--;
    return 0;
}

