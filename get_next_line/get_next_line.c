/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 15:35:29 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/26 16:26:54 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*
#include <fcntl.h>
#include <stdio.h>
*/

int	is_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_line(int fd, char *buff)
{
	char	*temp;
	int		ret;

	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	ret = 1;
	while (!is_line(buff) && ret)
	{
		ret = read(fd, temp, BUFFER_SIZE);
		if (!ret)
			break ;
		if (ret == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[ret] = 0;
		buff = ft_strcombine(buff, temp);
	}
	free(temp);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	char		**splitted;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = read_line(fd, buff);
	if (!buff)
		return (NULL);
	if (!buff[0])
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	splitted = ft_split_line(buff);
	line = ft_strdup(splitted[0]);
	free(buff);
	buff = ft_strdup(splitted[1]);
	free(splitted[0]);
	if (splitted[1])
		free(splitted[1]);
	free(splitted);
	return (line);
}
/*
int	main(int ac, char **av)
{
	char	*line;
	int		fd1;
	int		i;

	(void)ac;
	fd1 = open(av[1], O_RDONLY);
	line = get_next_line(fd1);
	i = 0;
	while (i < 6)
	{
		printf("line [%d]: %s", i, line);
		free(line);
		line = get_next_line(fd1);
		i++;
	}
	close(fd1);
	free(line);
//	system("leaks get_next_line");
	return (0);
}
*/
