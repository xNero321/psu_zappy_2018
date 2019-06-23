/*
** EPITECH PROJECT, 2019
** psu_zappy_2018
** File description:
** read_cmds.h
*/

#ifndef READ_CMDS_H
	#define READ_CMDS_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdbool.h>

	typedef struct circular_buffer_s
	{
		char buffer[2048];
		char *head;
		char *tail;
	} circular_buffer_t;

	void circular_buffer_init(circular_buffer_t *buffer);
	bool circular_buffer_read(circular_buffer_t *buffer, int fd);
	char *circular_buffer_get_to(circular_buffer_t *buffer, char *to);

#endif /* !READ_CMDS_H */
