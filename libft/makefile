CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_atoi.c \
		ft_memcpy.c \
		ft_memset.c \
		ft_split.c \
		ft_strlen.c \
		ft_printf/ft_printf.c \
		ft_printf/put_functions1.c \
		ft_printf/put_functions2.c
OBJS = $(SRCS:.c=.o)
NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re