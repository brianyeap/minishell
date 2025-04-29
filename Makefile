NAME    = minishell

SRC_DIRS = srcs libft
INC_DIR  = includes

# Find all .c files in the source directories
CFILES  = $(shell find $(SRC_DIRS) -type f -name "*.c")
OFILES  = $(CFILES:.c=.o)

# Compiler settings
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

# Libraries for readline
LIBS = -lreadline -lncurses

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

sanitize: fclean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address -g" $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all sanitize clean fclean re
