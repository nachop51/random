#ifndef SHELL_STRING_H
#define SHELL_STRING_H

char *_strchr(char *s, char c);
void *_memset(void *s, uint8_t b, uint32_t n);
uint32_t _strlen(char *s);
int32_t _strncmp(char *s1, char *s2, uint32_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strtok(char *str, char *delim);

#endif /* SHELL_STRING_H */
