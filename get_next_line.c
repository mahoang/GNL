/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahoang <mahoang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:44:45 by mahoang           #+#    #+#             */
/*   Updated: 2019/11/28 11:03:41 by mahoang          ###   ########.fr       */
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

// salut\n

int			to_free(char **str, int type)
{
	free(*str);
	*str = NULL;
	return (type);
}

int			ft_readline(char **stock, int fd)
{
	char	*str;
	char	*tmp;
	int		c;

	if (!*stock)
		*stock = ft_strdup("");
	if (!(str = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (!ft_strchr(*stock, '\n'))
	{
		if ((c = read(fd, str, BUFFER_SIZE)) == -1)
			return (to_free(&str, -1));
		if (c == 0)
			return(to_free(&str, 0));
		str[c] = '\0';
		tmp = *stock;
		*stock = ft_strjoin(*stock, str);
		free(tmp);
	}
	return (to_free(&str, 1));
}

size_t		ft_linelen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int			get_next_line(int fd, char **line)
{
	static char	*stock = NULL;
	char		*tmp;
	int			ret;

	if (fd <= -1 || line == NULL || BUFFER_SIZE < 1 || read(fd, stock, 0) == -1)
		return (-1);
	if ((ret = ft_readline(&stock, fd)) == -1)
		return (to_free(&stock, -1));
	else if (ret == 0)
	{
		*line = ft_strdup(stock);
		return (to_free(&stock, 0));
	}
	ret = ft_linelen(stock);
	*line = ft_substr(stock, 0, ret);
	tmp = stock;
	stock = ft_strdup(stock + ret + 1);
	return (to_free(&tmp, 1));
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

// int	main(int ac, char **av)
// {
// 	int	fd;
// 	char	*str;
// 	int	retval;

// 	if (ac == 1)
// 	{
// 		printf("not enough arguments\n");
// 		return (0);
// 	}
// 	fd = open(av[1], O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("fd a -1\n");
// 		return (0);
// 	}
// 	while ((retval = get_next_line(fd, &str)) > 0)
// 	{
// 		printf(">%s<\n", str);
// 		free(str);
// 	}
// 	printf("AFTER WHILE STR : >%s<\n", str);
// 	printf("retval = %d\n", retval);
// 	return 0;
// }
// #include <stdio.h>

// int main(int ac, char **av)
// {
// 	int fd;
// 	int fd2;
//     char *line;
// 	int ret = 1;
// 	int dpipe[2];
// 	int out = dup(1);
// 	pipe(dpipe);
// 	(void)ac;

// 	if (!(fd = open(av[1], O_RDONLY)))
// 		printf("main error\n");
// 	//Test normal
// 	printf("TEST NORMAL----------------------------------------------------------------\n");
// 	while ((ret = get_next_line(fd, &line)) > 0)
// 	{
// //		free(line);
// 		printf("\n===========================================================\n");
// 		printf("retour de gnl : %i\n", ret);
// 		printf("valeur de line : \"\x1b[32m%s\x1b[0m\"\n", line);
// 	}
// 	printf("retour de gnl : %i\n", ret);
// 	printf("valeur de line : \"\x1b[32m%s\x1b[0m\"\n", line);
// 	//Test 2 avec sortie standard
// 	printf("TEST STDIN----------------------------------------------------------------\n");
// 	fd = 1;
// 	dup2(dpipe[1], fd);
// 	write(fd, "test(01) of pipe input!\n", 24);
// 	write(fd, "i put this right after test 1\n", 31);
// 	close(dpipe[1]);
// 	dup2(out, fd);
// 	get_next_line(dpipe[0], &line);
// 	printf("string compare : %i\n", strcmp("test(01) of pipe input!", line));
// 	printf("valeur de line (pipe): \"\x1b[32m%s\x1b[0m\"\n", line);
// 	get_next_line(dpipe[0], &line);
// 	printf("string compare 2 : %i\n", strcmp("i put this right after test 1", line));
// 	printf("valeur de line (pipe): \"\x1b[32m%s\x1b[0m\"\n", line);
// //	free(line);
// 	//Test Multi FD
// 	printf("TEST MULTIFD----------------------------------------------------------------\n");
// 	if (!(fd2 = open("secondfile", O_RDONLY)))
// 		printf("main error\n");
// 	ret = get_next_line(fd2, &line);
// 	printf("retour de gnl : %i\n", ret);
// 	printf("valeur de line : \"\x1b[32m%s\x1b[0m\"\n", line);
// 	ret = get_next_line(fd2, &line);
// 	printf("valeur de line : \"\x1b[32m%s\x1b[0m\"\n", line);
// 	ret = get_next_line(fd, &line);
// 	printf("valeur de line : \"\x1b[32m%s\x1b[0m\"\n", line);
// //	free(line);
// 	printf("TEST IN----------------------------------------------------------------\n");
// 	while (1)
// 	{
// 		get_next_line(0, &line);
// 		printf("valeur de line (in): \"\x1b[32m%s\x1b[0m\"\n", line);
// 	}
// }
