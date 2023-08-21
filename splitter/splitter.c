#include "splitter.h"

int32_t main(int ac, char **av)
{
	if (ac != 2)
	{
		dprintf(2, "Usage: %s <filename>\n", av[0]);
		return (EXIT_FAILURE);
	}

	FILE *fp = fopen(av[1], "r");
	if (fp == NULL)
	{
		dprintf(2, "Error: Can't open file '%s'.\n", av[1]);
		return (EXIT_FAILURE);
	}

	list_t *head = NULL;
	char *line = NULL;
	size_t n = 0;

	while (getline(&line, &n, fp) != EOF)
	{
		if (add_node_end(&head, line) == NULL)
		{
			free_list(head);
			free(line);
			return (EXIT_FAILURE);
		}
	}

	print_list(head);

	free(line);
	free_list(head);

	if (fclose(fp) == EOF)
	{
		dprintf(2, "Error: Can't close file '%s'.\n", av[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
