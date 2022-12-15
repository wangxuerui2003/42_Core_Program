# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/15 11:00:46 by wxuerui           #+#    #+#              #
#    Updated: 2022/10/15 16:23:57 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

NAME		=	pipex
CC			=	gcc
HEADER		=	-I$(LIBFT_DIR)$(SRCS_DIR) -I$(INCLUDE_DIR)
CFLAGS		=	-Wall -Wextra -Werror $(HEADER)
LIBFTFLAGS	=	-L$(LIBFT_DIR) -lft
SRCS_DIR	=	srcs/
LIBFT_DIR	=	Libft/
OBJS_DIR	=	objs/
INCLUDE_DIR	=	includes/

#sources

SRC_FILES	=	px_main \
				px_utils

SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

#Colors

DEF_COLOR	=	\033[0;39m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[0;92m
YELLOW		=	\033[0;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m
RESET		=	\033[0m

#######

all:
				@mkdir -p $(OBJS_DIR)
				@make create_libft
				@make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo ".\c"

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(OBJS) -o $(NAME)
				@echo "\n$(GREEN)$(NAME) was created$(RESET)"

bonus:			all

create_libft:
				@make -C $(LIBFT_DIR)

clean:
				@rm -rf $(OBJS_DIR)
				@echo "$(BLUE)$(NAME): $(YELLOW)object files are cleaned$(RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@make fclean -C $(LIBFT_DIR)
				@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"

re:				fclean all

.PHONY:			all bonus create_libft clean fclean re
