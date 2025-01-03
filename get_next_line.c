/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imeslaki <imeslaki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:28:11 by imeslaki          #+#    #+#             */
/*   Updated: 2024/12/27 17:58:35 by imeslaki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reader(char *buffer, int fd)
{
	char	*tmp;
	char	*store_buffer;
	ssize_t	b;

	b = 1;
	tmp = malloc((size_t)BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (b != 0)
	{
		b = read(fd, tmp, BUFFER_SIZE);
		if (b == -1)
			return (free(tmp), free(buffer), NULL);
		tmp[b] = '\0';
		store_buffer = ft_join(buffer, tmp);
		free(buffer);
		buffer = ft_strdup(store_buffer);
		free(store_buffer);
		if (b != BUFFER_SIZE || ft_strchr(buffer) == 1)
		{
			b = 0;
			free(tmp);
		}
	}
	return (buffer);
}

char	*extract_line(char *buffer)
{
	char	*line;
	size_t	i;

	line = NULL;
	i = 0;
	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = malloc(i + 1 + (buffer[i] == '\n'));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*trash(char *buffer)
{
	char	*tmp;
	ssize_t	i;

	tmp = NULL;
	i = 0;
	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	if (ft_strchr(buffer) == 1)
	{
		while (buffer[i] != '\n')
			i++;
		if (buffer[i] != '\0')
			tmp = ft_strdup(&(buffer[++i]));
		free(buffer);
	}
	else if (ft_strchr(buffer) == 0)
	{
		free(buffer);
		tmp = NULL;
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), NULL);
	buffer = reader(buffer, fd);
	if (buffer == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	if (line == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = trash(buffer);
	return (line);
}
