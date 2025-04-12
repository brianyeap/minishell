CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

Compiler = gcc
Flags =  -Wall -Wextra -Werror

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OFILES)
	ar -cr $(NAME) $(OFILES)

%.o: %.c
	$(Compiler) $(Flags) -c $< -o $@ -I./

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re