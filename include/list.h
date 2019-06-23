/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** template_list.h
*/

#ifndef LIST_H_
    #define LIST_H_
    #include <stdbool.h>

    typedef struct list_s
    {
        struct list_s *next;
        struct list_s *prev;
    } list_t;

    #define list_push(a, b) list_add_item((void **)a, b, sizeof(*(b)))
    #define list_next(a) list_next_item((void **)a)
    #define list_prev(a) list_prev_item((void **)a)
    #define list_delete(a) list_delete_all((void **)a)
    #define list_remove(a) list_delete_item((void **)a)

    bool list_add_item(void **list, void *data, size_t data_size);
    bool list_next_item(void **list);
    bool list_prev_item(void **list);
    void list_delete_all(void **list);
    void list_delete_item(void **list);
#endif /* !LIST_H_ */
