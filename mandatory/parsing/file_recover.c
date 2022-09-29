#include "../main.h"

int	file_size(int fd)
{
	int		size;
	int		r;
	int		i;
	char	buffer[5000000];

	size = 1;
	i = 0;
	r = read(fd, buffer, 5000000);
	if (r <= 0)
	{
		write(1, "The file is empty\n", 18);
		return (0);
	}
	buffer[r + 1] = '\0';
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
			size++;
		i++;
	}
	return (size);
}

int	read_fd(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		write(1, "error : arguments is a directory\n", 33);
		return (0);
	}
	fd = open(file, O_RDONLY);
	if (fd <= 0)
	{
		write(1, "an error occured with the read of map\n", 38);
		return (0);
	}
	return (fd);
}

char	**read_file(int fd, int size)
{
	int		i;
	char	**file;

	i = 0;
	file = malloc(sizeof(char *) * (size + 1));
	if (!file)
		return (NULL);
	while (i < size)
	{
		file[i] = get_next_line(fd);
		i++;
	}
	file[i] = NULL;
	return (file);
}

char	**file_recover(char *str)
{
	char	**file;
	int		fd;
	int		size;

	file = NULL;
	fd = read_fd(str);
	if (fd <= 0)
		return (NULL);
	size = file_size(fd);
	close(fd);
	fd = read_fd(str);
	if (fd == 0)
		return (NULL);
	file = read_file(fd, size);
	if (!file)
	{
		free_tab(file);
		return (NULL);
	}
	return (file);
}
