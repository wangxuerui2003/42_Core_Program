# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 15:15:31 by wxuerui           #+#    #+#              #
#    Updated: 2023/01/18 15:15:29 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME		=	philo_bonus
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra $(HEADER) -pthread

ifeq ($(DEBUG), true)
	CFLAGS += -fsanitize=thread -g3
endif

HEADER		=	-I $(INC_DIR)
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/
INC_DIR		=	includes/

SRC_FILES	=	init \
				main \
				routine \
				utils

SRCS	=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS	=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

# Colors

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
				@make $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo ".\c"

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
				@echo "\n$(GREEN)$(NAME) was created$(RESET)"

clean:
				@rm -rf $(OBJS_DIR)
				@echo "$(BLUE)$(NAME): $(YELLOW)object files are cleaned$(RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"

re:				fclean all

.PHONY:			all bonus create_libft clean fclean re
	