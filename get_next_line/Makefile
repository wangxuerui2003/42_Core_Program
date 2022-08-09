# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/10 14:43:42 by wxuerui           #+#    #+#              #
#    Updated: 2022/07/26 20:57:44 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variable

NAME	= get_next_line
CC	= gcc
CFLAGS	= -Wall -Werror -Wextra #-fsanitize=address -g3

#sources

SRCS_FILES	= get_next_line get_next_line_utils
BONUS_FILES	= get_next_line_bonus get_next_line_utils_bonus

SRCS	= $(addsuffix .c, $(SRCS_FILES))
OBJS	= $(addsuffix .o, $(SRCS_FILES))
BONUS	= $(addsuffix .c, $(BONUS_FILES))
BOBJS	= $(addsuffix .o, $(BONUS_FILES))

##########

all:	$(NAME)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus:	$(BOBJS)	
		$(CC) $(CFLAGS) $(BOBJS) -o $(NAME)

clean:
		rm -rf *.o

fclean:	clean
		rm -rf $(NAME)

re:	fclean all bonus

.PHONY:	all clean fclean re
