/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:44:45 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/18 16:48:31 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		*ft_calloc(size_t count, size_t size)
{
	char		*tab;
	size_t		i;

	if (!(tab = malloc(size * count)))
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		tab[i] = '\0';
		i++;
	}
	return (tab);
}

char	*ft_readline(char *stock, int fd)
{
	char	*str;
	int		c;
	char	*tmp;

	if (stock == NULL)
		stock = ft_calloc(sizeof(char), 1);
	if (!(str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (NULL);
	while (!ft_strchr(stock, '\n'))
	{
		if ((c = read(fd, str, BUFFER_SIZE)) == -1)
			return (NULL);
		if (c == 0)
		{
			free(str);
			return (stock);
		}
		str[c] = '\0';
		tmp = ft_strdup(stock);
		free(stock);
		stock = ft_strjoin(tmp, str);
		free(tmp);
	}
	free(str);
	return (stock);
}

int		get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	int			i;
	char		*tmp;

	if ((fd <= -1 || line == NULL || BUFFER_SIZE < 1) || read(fd, stock, 0) < 0
	|| !(stock = ft_readline(stock, fd)))
	{
		free(stock);
		stock = NULL;
		return (-1);
	}
	i = 0;
	if (stock[i])
	{
		while (stock[i] != '\n' && stock[i])
			i++;
		*line = ft_substr(stock, 0, i);
		tmp = stock;
		stock = ft_strdup((stock + i + (stock[i] == '\n' ? 1 : 0)));
		if (tmp[i] == '\0')
		{
			free(tmp);
			return (0);
		}
		free(tmp);
		return (1);
	}
	*line = ft_strdup("");
	return (0);
}
