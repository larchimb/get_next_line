/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:41:23 by larchimb          #+#    #+#             */
/*   Updated: 2025/12/09 14:22:30 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchrcpy(const char *s, int c)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = (char *)s;
	while (s[i] && s[i] != (char)c)
		i++;
	i++;
	while (s[i])
	{
		ptr[j++] = ptr[i++];
	}
	ptr[j] = '\0';
	return ((char *)s);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	ptr = malloc(sizeof(const char) * ft_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_of_s1;
	size_t	len_of_s2;
	size_t	i;
	size_t	j;

	len_of_s1 = ft_strlen(s1);
	len_of_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	ptr = malloc(sizeof(char) * (len_of_s1 + len_of_s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2[j])
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[(len_of_s1 + len_of_s2)] = '\0';
	free((char *)s1);
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
		i++;
	return (i);
}
