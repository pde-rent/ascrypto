#include "ascrypto.h"

char    		*file_to_str(char *file_name)
{
	int     fd;
	int     i;
	int     handle;
	char    buf[BUFF_SIZE];
	char    *tmp;

	i = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1)
	{
		printf("Can't read input file\n");
		return NULL;
	}
	
	while ((handle = read(fd, buf, BUFF_SIZE)))
		i++;
	close(fd);
	tmp = (char *)malloc(sizeof(char) * (i * BUFF_SIZE + 1));
	fd = open(file_name, O_RDONLY);
	if ((handle = read(fd, tmp, (BUFF_SIZE * i + 1))))
		printf("Input file read\n");
	i = BUFF_SIZE * (i - 1) - 1;
	while (tmp[++i])
		if (tmp[i] < 32 || tmp[i] > 126)
			while(tmp[i])
			{
					tmp[i] = '\0';
					i++;
			}
	printf("Input string: %s\n", tmp);
	close(fd);
	return (tmp);
}

void	str_to_file(char *str, char *file_name)
{
	int handle;
	int fd;

	printf("Output string: %s\n", str);
	if (((fd = open(file_name, O_RDWR | O_TRUNC)) == -1))
	{
		printf("Can't write to output file\n");
		return ;
	}
    if ((handle = write(fd, str, strlen(str))))
		printf("Output file written\n");
	free(str);
	close(fd);
}