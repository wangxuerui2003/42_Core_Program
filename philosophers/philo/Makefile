# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 18:01:19 by wxuerui           #+#    #+#              #
#    Updated: 2023/02/28 14:04:10 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables

NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Werror -Wextra -pthread $(HEADER)

ifeq ($(DB), 1)
	CFLAGS	+=	-fsanitize=thread -g
endif

HEADER	=	-I $(INC_DIR)
INC_DIR	=	includes/
SRCS_DIR	=	srcs/
OBJS_DIR	=	objs/


#sources

SRC_FILES	=	main \
				routine \
				init \
				utils \

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

.PHONY:			all bonus create_libft clean fclean re%