/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:11 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/26 16:19:14 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
/*
#include <fcntl.h>
#include <stdio.h>
*/

/* return 1 if the string contains '\n' else 0 */
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

/* read BUFFER by BUFFER and return the final string that contains \n 
 * or encounter EOF.
 */
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

/* get the new line and update the static variable buff */
char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*line;
	char		**splitted;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buff[fd] = read_line(fd, buff[fd]);
	if (!buff[fd])
		return (NULL);
	if (!buff[fd][0])
	{
		free(buff[fd]);
		buff[fd] = NULL;
		return (NULL);
	}
	splitted = ft_split_line(buff[fd]);
	line = ft_strdup(splitted[0]);
	free(buff[fd]);
	buff[fd] = ft_strdup(splitted[1]);
	free(splitted[0]);
	if (splitted[1])
		free(splitted[1]);
	free(splitted);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	fd1 = open("test_files/test1.txt", O_RDONLY);
	fd2 = open("test_files/test2.txt", O_RDONLY);
	fd3 = open("test_files/test4.txt", O_RDONLY);
	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	system("leaks get_next_line");
	return (0);
}
*/
