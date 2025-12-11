/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:38:36 by larchimb          #+#    #+#             */
/*   Updated: 2025/12/11 15:57:27 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>

static char	*trim_to_the_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
	{
		free(str);
		return (NULL);
	}
	line[i--] = '\0';
	while (i >= 0)
	{
		line[i] = str[i];
		i--;
	}
	free(str);
	return (line);
}

static int	check_if_endline(char *str)
{
	size_t	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*fill_line(int fd, char *line, char buffer[BUFFER_SIZE + 1])
{
	int	bytes_read;

	while (check_if_endline(line) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		line = ft_strjoin_free(line, buffer);
	}
	line = trim_to_the_line(line);
	if (ft_strlen(line) == 0 && bytes_read <= 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = ft_strdup(buffer[fd]);
	line = fill_line(fd, line, buffer[fd]);
	ft_strchrcpy(buffer[fd], '\n');
	return (line);
}
/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		printf("%s", str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
	}
	close(fd);
} */
