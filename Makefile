NAME    = minishell

SRC_DIRS = srcs libft
INC_DIR  = includes

CFILES  = $(shell find $(SRC_DIRS) -type f -name "*.c")
OFILES  = $(CFILES:.c=.o)

CC       = gcc
CFLAGS   = -Wall -Wextra -Werror
INCLUDES = -I$(INC_DIR)

# Detect platform (Darwin = macOS, Linux = Linux)
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	# macOS: Use Homebrew GNU Readline (if installed)
	BREW_PREFIX := $(shell brew --prefix readline 2>/dev/null)
	ifneq ($(BREW_PREFIX),)
		CFLAGS   += -I$(BREW_PREFIX)/include
		LDFLAGS  += -L$(BREW_PREFIX)/lib
	endif
	LIBS = -lreadline -lncurses
else
	# Linux (standard locations)
	LIBS = -lreadline -lncurses
endif

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OFILES) $(LDFLAGS) $(LIBS)

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
