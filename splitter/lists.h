#ifndef _LISTS_H
#define _LISTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct list_s
{
	char *line;
	struct list_s *next;
} list_t;

list_t *add_node_end(list_t **head, char *line);
void free_list(list_t *head);
void print_list(list_t *h);
char **list_to_vector(list_t *h);

#endif /* _LISTS_H */
