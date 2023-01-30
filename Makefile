NAME = pipex
CC = clang #-g -fsanitize=address
CFLAGS = -I./includes

SRCS_DIR = sources
SRCS = main.c utils.c

OBJS_DIR = $(SRCS_DIR)/objs
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LFLAGS = -L./libft -lft

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $< \033[0;32m✔\033[0m"
	@$(CC) -Wall -Wextra -Werror -I/usr/include -O3 $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make --no-print-directory -C $(LIBFT_DIR)

bonus: 

clean:
	@rm -rf $(OBJS_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@echo "===> Objects deleted"

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@echo "===> Binaries deleted"

re: fclean all

.PHONY: all clean fclean re
