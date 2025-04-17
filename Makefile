NAME    = minishell

SRC_DIRS = srcs libft
FT_PRINTF_DIR = libft/ft_printf
INC_DIR  = includes

# Find all .c files in the source directories and the helpers directory
CFILES  = $(shell find $(SRC_DIRS) -type f -name "*.c")

OFILES  = $(CFILES:.c=.o)

# Compiler settings
Compiler = gcc
Flags    = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

all: $(NAME)

$(NAME): $(OFILES)
	$(Compiler) $(Flags) -o $(NAME) $(OFILES) -lreadline

%.o: %.c
	$(Compiler) $(Flags) -c $< -o $@ $(INCLUDES)

sanitize: fclean
	$(MAKE) Flags="$(Flags) -fsanitize=address -g" $(NAME)

clean:
	@rm -f $(OFILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all sanitize clean fclean re
