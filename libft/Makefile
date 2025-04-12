Library = libft

CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

Compiler = gcc
Flags =  -Wall -Wextra -Werror

OUTN = $(Library).a
NAME = $(OUTN)

all: $(NAME)

$(NAME): $(OFILES)
	ar -cr $(OUTN) $(OFILES)

%.o: %.c
	$(Compiler) $(Flags) -c $< -o $@ -I./

clean:
	rm -rf $(OFILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re