/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 23:46:52 by oshelba           #+#    #+#             */
/*   Updated: 2021/12/06 23:51:16 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_read(int fd, char *n_line)
{
	char	*buf;
	int		n_b;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	n_b = 1;
	while (!ft_strchr(n_line, '\n') && n_b > 0)
	{
		n_b = read(fd, buf, BUFFER_SIZE);
		if (n_b == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[n_b] = '\0';
		n_line = ft_strjoin(n_line, buf);
	}
	free(buf);
	return (n_line);
}

char	*ft_new_line(char *n_line)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen_gnl(n_line);
	if (!n_line[i])
	{
		free(n_line);
		return (NULL);
	}
	j = (ft_strlen(n_line) - i + 1);
	str = (char *)malloc(sizeof(char) * j);
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (n_line[i])
		str[j++] = n_line[i++];
	str[j] = '\0';
	free(n_line);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*n_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	n_line = line_read(fd, n_line);
	if (!n_line)
		return (NULL);
	line = ft_strdup_gnl(n_line);
	n_line = ft_new_line(n_line);
	return (line);
}
