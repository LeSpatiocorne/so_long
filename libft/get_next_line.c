/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:22:03 by nidruon           #+#    #+#             */
/*   Updated: 2025/04/28 17:41:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_calloc(ft_strlen(buffer) - i, sizeof(char));
	if (!new_buffer)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

static char	*handle_read(int fd, char *buffer, char *temp)
{
	int		bytes_read;
	char	*new_buffer;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		new_buffer = ft_strjoin(buffer, temp);
		if (!new_buffer)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = new_buffer;
	}
	free(temp);
	return (buffer);
}

static char	*read_file(int fd, char *buffer)
{
	char	*temp;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (NULL);
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	buffer = handle_read(fd, buffer, temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[4096];
	char		*line;

	if (fd < 0 || fd >= 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = read_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = update_buffer(buffer[fd]);
	return (line);
}
