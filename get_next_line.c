#include "get_next_line.h"

#ifndef BUFFER_SIZE
 #define BUFFER_SIZE 42
#endif

char *ft_calloc(int s)
{
	int i = 0;
    	char *dest;

    	if(s < 0)
        	return(NULL);
   	 dest = malloc(sizeof(char) * s);
    	while(i < s)
    	{
        	dest[i] = '\0';
            	i++;
    	}
    	return(dest);
}

int  ft_is_nl(char *str)
{
    int i = 0;

    if(!str)
        return(0);
    while(str[i])
    {
        if(str[i] == '\n')
            return(1);
        i++;
    }
    return(0);
}

int ft_strlen(char *str)
{
    int i = 0;
    if(!str)
        return(0);
    while(str[i])
        i++;
    return(i);
}

char *ft_strjoin(char *str, char *buff)
{
    int j = 0;
    int i = 0;
    char *dest;

    if(!str)
        str = ft_calloc(1);
    if(!str && !buff)
        return(NULL);
    if(!buff)
        return(str);
	
    dest = ft_calloc(ft_strlen(str) + ft_strlen(buff) + 1);
    while(str[i])
    {
        dest[i] = str[i];
        i++;
    }
    while(buff[j])
    {
        dest[i] = buff[j];
        j++;
        i++;
    }
    return(free(str), dest);
} 

char *ft_ext_line(char *str)
{
    int j = 0;
    int i = 0;
    char *dest;

    if(!str[0])
        return(NULL);
    while(str[i] && str[i] != '\n')
        i++;
    if(str[i] == '\n')
        i++;
    dest = ft_calloc(i + 1);
    while(str[j] && str[j] != '\n')
    {
        dest[j] = str[j];
        j++;
    }
    if (str[j] == '\n')
        dest[j] = '\n';
    return(dest);
}

char *ft_ext_str(char *str)
{
    int j = 0;
    int i = 0;
    char *dest; 

    if(!str)
        return(NULL);
    while(str[i] && str[i] != '\n')
        i++;
    if(str[i] == '\0')
        return(free(str), NULL);
    i++;
    dest = ft_calloc((ft_strlen(str) - i) + 1);
    while(str[i])
    {
        dest[j] = str[i];
        j++;
        i++;
    }
    return(free(str), dest);
}

char *get_next_line(int fd)
{
    static char *str = NULL;
    char *line = NULL;
    char buffer[BUFFER_SIZE + 1];
    int rd = 1;
    
    if (BUFFER_SIZE <= 0 || fd < 0)
        return (NULL);
    while(rd > 0 && !ft_is_nl(line))
    {
        rd = read(fd, buffer, BUFFER_SIZE);
        if(rd == -1)
            return(free(str), NULL);
        buffer[rd] = '\0';
        str = ft_strjoin(str, buffer);
    }
    line = ft_ext_line(str);
    str = ft_ext_str(str);
    return(line);
}

#include <fcntl.h>
#include <stdio.h>
int main(void)
{
    int fd;
    char *line;

    fd = open("text.txt", O_RDONLY);
    while(1)
    {
        line = get_next_line(fd);
        if(line == NULL)
        {
            free(line);
            break;
        }
        printf("%s", line);
        free(line);
    }
    return(0);
}
