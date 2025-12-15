/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:38:36 by larchimb          #+#    #+#             */
/*   Updated: 2025/12/15 10:18:11 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
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
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*fullfill_complete_line(int fd, char *complete_line, char *buffer)
{
	int	bytes_read;

	while (check_if_endline(complete_line) == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(complete_line);
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
	return (complete_line);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*complete_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	complete_line = ft_strdup(buffer);
	complete_line = fullfill_complete_line(fd, complete_line, buffer);
	ft_strchrcpy(buffer, '\n');
	return (complete_line);
}
