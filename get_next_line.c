/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:01:38 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/01 19:38:49 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	static char			*stock;
	char				str[BUFFER_SIZE + 1];
	int					c;
	int					d;
	char				*temp;

	if ( !fd || !line)
		return (-1);
	c = 1;
	while (!ft_strchr(str, '\n') && c > 0)
	{
		c = read(fd, str, BUFFER_SIZE);
		if (stock)
		{
			str[BUFFER_SIZE] = '\0';
			stock = ft_strjoin(stock, str);
		}
		else
			stock = strdup(str);
	}
	temp = ft_strchr(str, '\n');
	if ( temp && c >= 0)
	{
		*line = ft_substr(stock, 0, (ft_strlen(stock) - (ft_strlen(temp))));/* ptet mauvaise fonction a utiliser*/
		stock = ft_substr(stock, ft_strlen(*line), ft_strlen(stock) - ft_strlen(*line));
		return (1);
	}
	else
	{
		*line = ft_substr(stock, 0, (ft_strlen(stock) - (ft_strlen(temp))));
		stock = ft_substr(stock, ft_strlen(str), ft_strlen(stock) - ft_strlen(*line));
		return (0);
	}
}

int main(int argc, char **argv)
{
	int fd;
	int ret;
	int line;
	char *buff;

	line = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &buff)) > 0)
		{
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
			free(buff);
		}
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("[Return: %d]\n  -----------\nEnd of file\n", ret);
		close(fd);
	}
	if (argc == 1)
	{
		while ((ret = get_next_line(0, &buff)) > 0)
			printf("[Return: %d] Line #%d: %s\n", ret, ++line, buff);
		if (ret == -1)
			printf("-----------\nError\n");
		else if (ret == 0)
			printf("-----------\nEnd of stdin\n");
		close(fd);
	}
	return (0);
}
