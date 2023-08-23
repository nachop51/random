#include "splitter.h"

/**
 * @brief adds a new node at the end of a list_t list
 * @param head list_t Poiter to the head of the list
 * @param line (char *) to add to the list
 *
 * @return address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, char *line)
{
	if (!head)
		return (NULL);

	list_t *new_node = NULL;

	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	new_node->line = strdup(line);
	if (new_node->line == NULL)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
		return (new_node);
	}

	list_t *last_node = *head;

	while (last_node->next != NULL)
		last_node = last_node->next;

	last_node->next = new_node;
	return (new_node);
}

/**
 * @brief frees a list_t list
 * @param head list_t Pointer to the head of the list
 */
void free_list(list_t *head)
{
	list_t *tmp = NULL;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->line);
		free(tmp);
	}
}

/**
 * @brief prints all the elements of a list_t list
 * @param h list_t Pointer to the head of the list
 */
inline void print_list(list_t *h)
{
	while (h)
		printf("%s", h->line), h = h->next;
}

/**
 * @brief returns the number of elements in a linked list
 * @param h list_t Pointer to the head of the list
 * @return size_t Number of elements in the list
 */
size_t list_len(list_t *h)
{
	size_t i = 0;

	while (h)
		h = h->next, i++;
	return (i);
}

/**
 * @brief converts a list to a vector
 * @param h list_t Pointer to the head of the list
 * @return char ** Pointer to the vector
 */
char **list_to_vector(list_t *h)
{
	int i = 0;
	char **v = NULL;

	if (!h)
		return (NULL);
	v = malloc(sizeof(char *) * (list_len(h) + 1));
	if (!v)
		return (NULL);
	while (h)
	{
		v[i] = strdup(h->line);
		h = h->next, i++;
	}
	v[i] = NULL;
	return (v);
}

void free_vector(char **vector)
{
	for (uint16_t i = 0; vector[i] != NULL; i++)
		free(vector[i]);
	free(vector);
}

void print_vector(char **v)
{
	printf("Vector:\n[");
	for (uint16_t i = 0; v[i] != NULL; i++)
		i != 0 ? printf(", ") : 0, printf("\"%s\"", v[i]);
	printf(", NULL]\n");
}
