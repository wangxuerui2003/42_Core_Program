/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 17:53:31 by wxuerui           #+#    #+#             */
/*   Updated: 2022/07/14 14:19:23 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 15
# endif

char	*get_next_line(int fd);
char	*ft_strcombine(char *s1, char *s2);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s1);
char	**ft_split_line(char *buff);
int		is_line(char *line);

#endif