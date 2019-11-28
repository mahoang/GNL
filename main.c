/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 09:57:40 by lfalkau           #+#    #+#             */
/*   Updated: 2019/11/28 11:16:20 by mahoang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int		main(int ac, char **av)
{
	char *line;
	int fd;
	int ret;

	if (ac < 2) //loop into standard entry
	{
		fd = 0;
		ret = 1;
		while (ret) {
			ret = get_next_line(fd, &line);
			printf("%d: %s\n", ret, line);
			free(line);
		}
		return (0);
	}
	if (ac == 2) // read n lines from xxx and write the gnl output for each
	{
		int nb_lines = atoi(av[1]);
		fd = open("logs", O_RDONLY);
		for (int i = 0; i < nb_lines; i++) {
			ret = get_next_line(fd, &line);
			printf("%d: %s\n", ret, line);
			free(line);
		}
		close(fd);
		return (0);
	}
	if (ac > 2) // Read n lines from several files, write the putput for each
	{
		if (ac % 2 == 0)
			return (0);
		int i = 0;
		while (i < ac / 2)
		{
			fd = open(av[2 * i + 1], O_RDONLY);
			for (int j = 0; j < atoi(av[2 * i + 2]); j++) {
				ret = get_next_line(fd, &line);
				printf("%d: %s\n", ret, line);
				free(line);
			}
			printf("\n");
			i++;
		}
	}
	return (0);
}

#include <stdio.h>

int			main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) >= 0)
	{
		printf("ret = %d || line = %s\n", ret, line);
		free(line);
		if (ret == 0)
			break ;
	}
	return (0);
}

__attribute__((destructor))void rdfsfd()
{
	while (1);
}
