#
#

NOM=libmlx.a
CFLAGS+=-O2 -w 
SRC= mlx_shaders mlx_new_window mlx_init_loop mlx_new_image mlx_xpm mlx_int_str_to_wordtab
SRC+= mlx_png mlx_mouse
OBJ=$(addsuffix .o, $(SRC))

# add to match string put with X11 in size and position
CFLAGS+=-DSTRINGPUTX11

#colours
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0m

%.o:	%.c
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo ".\c"

%.o:	%.m
	@$(CC) $(CFLAGS) -c $^ -o $@
	@echo ".\c"

all: $(NOM)

$(NOM):	$(OBJ)
	@ar -rcs $(NOM) $(OBJ)
	@echo "\n$(GREEN)$(NOM) was created$(RESET)"

clean:
	@rm -f $(OBJ) *~
	@rm -f mlx_app
	@echo "$(BLUE)$(NOM): $(YELLOW)object files are cleaned$(RESET)"

fclean:	clean
		@rm -f $(NOM)
		@echo "$(BLUE)$(NOM): $(MAGENTA)$(NAME) was deleted$(RESET)"

re: clean all
