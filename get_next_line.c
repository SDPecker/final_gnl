#include "get_next_line.h"

char 	*get_next_line(int fd)
{
	static char	*memory;
	char		*buf;
	char		*res;
	int			reader;

	reader = 1;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (reader != 0 && ft_strchr(memory, '\n') == NULL)
	{
		reader = read(fd, buf, BUFFER_SIZE);
		if (reader == -1)
			return (get_free(&buf));
		buf[reader] = 0;
		memory = ft_strjoin(memory, buf);
	}
	free(buf);
	res = get_line(memory);
	if (ft_strlen(memory) == 0)
		return (get_free(&memory));
	get_memory(&memory, res);
	return (res);
}

char	*get_line(char *memory)
{
	char		*ptr;
	char		*line;

	ptr = ft_strchr(memory, '\n');
	if (ptr == NULL && *memory != 0)
		line = ft_strdup(memory);
	else if (ptr != NULL)
		line = ft_substr(memory, 0, (ptr - memory) + 1);
	else
		return (NULL);
	return (line);
}

int	get_memory(char **memory, char *line)
{
	char	*tmp_str;

	tmp_str = ft_strdup(*memory + (ft_strlen(line)));
	free(*memory);
	*memory = tmp_str;
	if (*memory == NULL)
		return (0);
	return (1);
}

char	*get_free(char **memory)
{
	free(*memory);
	*memory = NULL;
	return (NULL);
}
