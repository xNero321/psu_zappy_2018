/*
** EPITECH PROJECT, 2019
** PSU_zappy_2018
** File description:
** template_list.h
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"

bool list_add_item(void **list, void *data, size_t data_size)
{
	list_t *new_node = malloc(sizeof(list_t) + data_size);
	list_t *node = (list_t *) ((*list == NULL) ? NULL : ((list_t *)\
		(*list) - 1));

	if (new_node == NULL) {
		ERROR("Error while allocating memory");
		return (false);
	}
	memcpy((((char *)new_node) + sizeof(list_t)), data, data_size);
	new_node->next = NULL;
	if (node == NULL) {
		*list = ((char *)new_node + sizeof(list_t));
		new_node->prev = NULL;
	} else {
		while (node->next != NULL)
			node = node->next;
		node->next = new_node;
		new_node->prev = node;
	}
	return (true);
}

bool list_next_item(void **list) {
	list_t *node = ((list_t *)(*list)) - 1;

	if (*list == NULL || node->next == NULL) {
		return (false);
	}
	node = node->next;
	*list = (void *)(node + 1);
	return (true);
}

bool list_prev_item(void **list) {
	list_t *node = ((list_t *)(*list)) - 1;

	if (*list == NULL || node->prev == NULL) {
		return (false);
	}
	node = node->prev;
	*list = (void *)(node + 1);
	return (true);
}

void list_delete_all(void **list)
{
	list_t *node = ((list_t *)(*list)) - 1;
	list_t *tmp_node;

	if (list == NULL)
		return ;
	while (node) {
		tmp_node = node;
		node = node->next;
		free(tmp_node);
	}
}

void list_delete_item(void **list)
{
	list_t *node = ((list_t *)(*list)) - 1;

	if (*list != NULL)
		return ;
	if (node->next)
		node->next->prev = node->prev;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		*list = node->next + 1;
	else
		*list = NULL;
	free(node);
}
