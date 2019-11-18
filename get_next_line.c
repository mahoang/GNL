/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:44:45 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/18 17:00:22 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char		*ft_readline(char *stock, int fd, int c)
{
	char	*str;
	char	*tmp;

	if (!stock)
		if (!(stock = malloc(1)))
			return (NULL);
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

size_t		ft_linelen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char		*to_free(char *str)
{
	free(str);
	str = NULL;
	return (str);
}

int			get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	int			i;
	char		*tmp;

	i = 0;
	if (fd <= -1 || line == NULL || BUFFER_SIZE < 1 || read(fd, stock, 0) == -1)
		return (-1);
	if (!(stock = ft_readline(stock, fd, i)))
		to_free(stock);
	if (stock[i])
	{
		i = ft_linelen(stock);
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
