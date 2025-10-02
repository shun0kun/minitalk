CFLAGS = -Wall -Wextra -Werror -Ilibft
LDFLAGS = -Llibft -lft
LIBFT = libft/libft.a

all: server client

server: server.c $(LIBFT)
	cc $(CFLAGS) $< -o $@ $(LDFLAGS)

client: client.c $(LIBFT)
	cc $(CFLAGS) $< -o $@ $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean

fclean: clean
	rm -f server client
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
