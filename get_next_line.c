#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int     is_new_line(char *str)
{
    int i;

    if (!str)
        return (0);
    i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
int     str_len(char *s)
{
    int i;

    if (!s)
        return (0);
    i = 0;
    while (s[i])
        i++;
    return (i);
}
char    *str_join(char *s1, char *s2)
{
    int     i;
    int     j;
    char *res;

    if (!s1)
    {
        s1 = malloc(sizeof(char) * 1);
        s1[0] = '\0';
    }
    if (!s1 || !s2)
        return (NULL);
    res = malloc(sizeof(char) * ((str_len(s1) + str_len(s2)) + 1));
    if (!res)
        return (NULL);
    i = -1;
    while (s1[++i])
        res[i] = s1[i];
    j = 0;
    while (s2[j])
    {
        res[i] = s2[j];
        i++;
        j++;
    }
    res[i] = '\0';
    free(s1);
    return (res);
}

char    *get_new_left(char *str)
{
    int     i;
    int     j;
    char    *res;

    if (!str[0])
    {
        free(str);
        return (NULL);
    }
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    res = malloc(sizeof(char) * (str_len(str) - i + 1));
    if (!res)
        return (NULL);
    i++;
    j = 0;
    while (str[i])
    {
        res[j] = str[i];
        i++;
        j++;
    }
    res[j] = '\0';
    free(str);
    return (res);
}

char    *get_line(char *str)
{
    int     i;
    char    *line;

    if (!str)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    line = malloc(sizeof(char) * (i + 2));
    if (!line)
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
    {
        line[i] = str[i];
        i++;
    }
    if (str[i] == '\n')
    {
        line[i] = '\n';
        i++;
    }
    line[i] = '\0';
    return (line);
}

char    *get_left(char *str, int fd)
{
    int     readed;
    char    *buff;

    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (NULL);
    readed = 1;
    while (readed != 0 && !is_new_line(str))
    {
        readed = read(fd, buff, BUFFER_SIZE);
        if (readed == -1)
        {
            free(buff);
            return (NULL);
        }
        buff[readed] = '\0';
        str = str_join(str, buff);
    }
    free(buff);
    return (str);
}

char    *get_next_line(int fd)
{
    static char *left;
    char        *line;

    if (fd < 0 || BUFFER_SIZE < 1)
        return (NULL);
    left = get_left(left, fd);
    if (!left)
        return (NULL);
    line = get_line(left);
    left = get_new_left(left);
    return (line);
}
/*
int main(void)
{   
    int   fd;

    fd = open("test.txt", O_RDONLY);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    return (0);
}*/