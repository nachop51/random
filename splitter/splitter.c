#include "splitter.h"

/**
 * @brief splits a string into tokens
 * @param str (char *) string to split
 *
 * @return (char **) array of tokens
 */
char **splitter(char *str)
{
    list_t *tokens = NULL;
    char **token_vector = NULL, buffer[1024] = {0}, c = '\0';
    uint16_t j = 0;

    for (uint16_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '"' || str[i] == '\'')
        {
            c = str[i], i++;
            while (str[i] != c)
            {
                if (str[i] == '\0')
                {
                    free_list(tokens);
                    return (NULL);
                }
                buffer[j++] = str[i++];
            }
        }
        else if (str[i] != ' ')
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
        if (add_node_end(&head, strtok(line, "\n")) == NULL)
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
            dprintf(2, "Something went wrong splitting the line.\n");
            break;
            return (EXIT_FAILURE);
        }
        print_vector(tokens);
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
