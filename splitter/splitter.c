#include "splitter.h"

void free_vector(char **vector)
{
	for (uint16_t i = 0; vector[i] != NULL; i++)
		free(vector[i]);
	free(vector);
}

char **splitter(char *str)
{
	list_t *tokens = NULL;
	char *tok = NULL, **token_vector = NULL, buffer[1024] = {0};
	uint16_t j = 0;

	for (uint16_t i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != ' ' && str[i] != '"' && str[i] != '\'')
			buffer[j++] = str[i];
		else
		{
			if (j != 0)
			{
				buffer[j] = '\0';
				if (add_node_end(&tokens, buffer) == NULL)
				{
					free_list(tokens);
					return (NULL);
				}
				j = 0, memset(buffer, 0, sizeof(buffer));
			}
		}
	}

	while (tok != NULL)
	{
		if (add_node_end(&tokens, tok) == NULL)
		{
			free_list(tokens);
			return (NULL);
		}
		tok = strtok(NULL, " \t\n");
	}

	token_vector = list_to_vector(tokens);
	free_list(tokens);
	return (token_vector);
}

int32_t main(int ac, char **av)
{
	// * --------------- Setup ---------------
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
	uint64_t n = 0;

	while (getline(&line, &n, fp) != EOF)
	{
		if (add_node_end(&head, line) == NULL)
		{
			free_list(head);
			free(line);
			return (EXIT_FAILURE);
		}
	}

	// * --------------- Split ---------------

	char **tokens = NULL;

	list_t *current = head;

	while (current != NULL)
	{
		printf("Line: \"%s\"\n", current->line);
		tokens = splitter(current->line);
		if (tokens == NULL)
		{
			perror("Error: ");
			free_list(head);
			free(line);
			return (EXIT_FAILURE);
		}
		printf("Tokens:\n[");
		for (uint16_t i = 0; tokens[i] != NULL; i++)
			i != 0 ? printf(", ") : 0, printf("\"%s\"", tokens[i]);
		printf("]\n");
		current = current->next;
		free_vector(tokens);
	}

	// * --------------- Cleanup ---------------

	free(line);
	free_list(head);

	if (fclose(fp) == EOF)
	{
		dprintf(2, "Error: Can't close file '%s'.\n", av[1]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
