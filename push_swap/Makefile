# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 20:43:19 by wxuerui           #+#    #+#              #
#    Updated: 2022/11/29 20:59:27 by wxuerui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# variables

NAME		=	push_swap
CHECKER		=	checker
CC			=	gcc
HEADER		=	-I$(LIBFT_DIR)$(SRCS_DIR) -I$(INCLUDE_DIR)
CFLAGS		=	-Wall -Wextra -Werror $(HEADER)
LIBFTFLAGS	=	-L$(LIBFT_DIR) -lft
SRCS_DIR	=	srcs/
BONUS_DIR	=	bonus/
LIBFT_DIR	=	Libft/
OBJS_DIR	=	objs/
BONUS_OBJS_DIR	=	bonus_objs/
INCLUDE_DIR	=	includes/

#sources

SRC_FILES	=	push_swap \
				operations1 \
				operations2 \
				ps_utils \
				check_input \
				sort_small \
				sort_big

BONUS_FILES	=	checker \
				checker_ops \
				checker_ops2 \
				cheating_ops \
				check_checker_input \
				checker_utils \

SRCS		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))
BONUS	= $(addprefix $(BONUS_DIR), $(addsuffix .c, $(BONUS_FILES)))
BONUS_OBJS	= $(addprefix $(BONUS_OBJS_DIR), $(addsuffix .o, $(BONUS_FILES)))

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

bonus:
				@mkdir -p $(BONUS_OBJS_DIR)
				@make create_libft
				@make $(CHECKER)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo ".\c"

$(BONUS_OBJS_DIR)%.o: $(BONUS_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@
				@echo ".\c"

$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(OBJS) -o $(NAME)
				@echo "\n$(GREEN)$(NAME) was created$(RESET)"

$(CHECKER):		$(BONUS_OBJS)
				@$(CC) $(CFLAGS) $(LIBFTFLAGS) $(BONUS_OBJS) -o $(CHECKER)
				@echo "\n$(GREEN)$(CHEKCER) was created$(RESET)"

create_libft:
				@make -C $(LIBFT_DIR)

clean:
				@rm -rf $(OBJS_DIR)
				@rm -rf $(BONUS_OBJS_DIR)
				@echo "$(BLUE)$(NAME): $(YELLOW)object files are cleaned$(RESET)"

fclean:			clean
				@rm -rf $(NAME)
				@rm -rf $(CHECKER)
				@make fclean -C $(LIBFT_DIR)
				@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"
				@echo "$(BLUE)$(NAME): $(MAGENTA)$(CHECKER) was deleted$(RESET)"

re:				fclean all

.PHONY:			all bonus create_libft clean fclean re