NAME = cub3d

# SOURCES
MAIN = $(addprefix srcs/, main.c)

ALL_SRCS +=	$(MAIN)

# OBJETS
OBJ_MAIN		= $(MAIN:.c=.o)

ALL_OBJS		+=	$(OBJ_MAIN)

# INCLUDES
INCLUDES_OPT = -Iincludes -I$(LIBFT_PATH)/includes -I$(MLX_PATH) -I/usr/include -Imlx

CFLAGS = -Wall -Werror -Wextra

MAKE_FLAGS		+=	--no-print-directory
MAKE_FLAGS		+=	-C

LIBFT_PATH = ./libft

# MLX
MLX_PATH = ./minilibx-linux
MLX_LIBS = $(MLX_PATH)/libmlx.a $(MLX_PATH)/libmlx_Linux.a -lX11 -lXext

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

NO_COLOR = "\033[0m"

# Rules
all: $(LIBFT_PATH)/libft.a $(MLX_PATH)/libmlx.a $(NAME)

$(NAME): $(ALL_OBJS)
	cc $(CFLAGS) $^ $(LIBFT_PATH)/libft.a $(MLX_LIBS) -o $(NAME)
	@echo $(BBlue)$(GRAS)"making cub3d 🆗" $(NO_COLOR)

$(LIBFT_PATH)/libft.a:
	@make $(MAKE_FLAGS) $(LIBFT_PATH)

$(MLX_PATH)/libmlx.a:
	@make -C $(MLX_PATH)

.c.o:
	cc $(CFLAGS) $(INCLUDES_OPT) -c $< -o ${<:.c=.o}

norm:
	-@norminette -R CheckForbiddenSourceHeader $(ALL_SRCS)
	-@norminette -R CheckDefine $(INCS)

val: all
	valgrind --leak-check=full --show-below-main=no --show-leak-kinds=all --track-fds=yes --trace-children=yes --suppressions=.supp.supp ./minishell

clean:
	@rm -rf $(ALL_OBJS)
	@make $(MAKE_FLAGS) $(LIBFT_PATH) fclean
	@echo $(BBlue)$(GRAS)"deleting cub3d 🚮"$(NO_COLOR)

fclean: clean
	@rm -f $(NAME)
		
re: fclean all