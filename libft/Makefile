NAME = libft.a

CFLAGS = -Wall -Wextra -Werror

# Source files
LIB_SRCS = $(wildcard srcs/*.c)

INCLUDES = -Iincludes 

# Object files
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Archives
AR = ar rc 

# Colors
RED	= "\033[0;31m"
GREEN = "\033[0;32m"
GRAS = "\033[1m"
NO_COLOR = "\033[0m"

# progress bar
define progress_bar
	@echo -n $(GREEN)"["
	@for i in $$(seq 1 $(words $(LIB_SRCS))); do \
		echo -n "■"; \
		sleep 0.01; \
	done
	@echo "]" $(GRAS)"Libft maked.✅"$(NO_COLOR)
endef

# progress bar
define un_progress_bar
	@echo -n $(RED)"["
	@for i in $$(seq 1 $(words $(LIB_SRCS))); do \
		echo -n "■"; \
		sleep 0.01; \
	done
	@echo "]" $(GRAS)"Libft deleted.🚯"$(NO_COLOR)
endef

# rules
all : $(NAME)

$(NAME) : $(LIB_OBJS)
	@$(AR) $(NAME) $(LIB_OBJS)
	@$(call progress_bar)

.c.o: 
	@cc $(CFLAGS) $(INCLUDES) -c $< -o ${<:.c=.o}

clean:
	@rm -rf ${LIB_OBJS}
	@$(call un_progress_bar)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re