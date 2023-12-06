NAME := minitalk
SERVER_EXEC := server
CLIENT_EXEC := client
CC := cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a

all: $(NAME)

$(NAME): $(SERVER_EXEC) $(CLIENT_EXEC)

$(LIBFT):
	make -C $(LIBFT_PATH)

%: %.c $(LIBFT)
	$(CC) $(CFLAGS) $< $(LIBFT) -o $@

clean:
	make clean -C $(LIBFT_PATH)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -f $(SERVER_EXEC) $(CLIENT_EXEC)

re: fclean all

.PHONY: all $(NAME) clean fclean re
