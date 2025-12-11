/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:38:36 by larchimb          #+#    #+#             */
/*   Updated: 2025/12/11 12:37:32 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

#include <stdio.h>

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

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*complete_line;
	int	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	complete_line = ft_strdup(buffer);
	bytes_read = 1;
	while (check_if_endline(complete_line) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(complete_line);
			buffer[0] = 0;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		complete_line = ft_strjoin_free(complete_line, buffer);
	}
	complete_line = trim_to_the_line(complete_line);
	if (ft_strlen(complete_line) == 0 && bytes_read <= 0)
	{
		free(complete_line);
		return (NULL);
	}
	ft_strchrcpy(buffer, '\n');
	return (complete_line);
}
/* #include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
