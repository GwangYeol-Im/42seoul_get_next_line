#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (void)
{
    int fd;
    int i;
    int j;
    char    *line = 0;
    char    *lineadress[66];

    j = 1;
    if (!(fd = open("4_newlines", O_RDONLY)))
    {
        printf("\nError in open\n");
        return (0);
    }
    while ((i = get_next_line(fd, &line)) > 0)
    {
        printf("|%s\n", line);
        lineadress[j - 1] = line;
        j++;
    }
    printf("|%s\n", line);
    free(line);
    close(fd);
    if (i == -1)
		printf ("\nError in Fonction - Returned -1\n");
	else if (j == 66)
		printf("\nRight number of lines\n");
	else if (j != 66)
		printf("\nNot Good - Wrong Number Of Lines\n");
	while (--j > 0)
		free(lineadress[j - 1]);
    return (0);
}