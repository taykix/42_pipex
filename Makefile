CC = gcc
CFLAGS = -g -Wall -Werror -Wextra
SRCS = ft_pipex.c \
       utils.c \
	   handle_script.c \
	   handle_path.c \
	   handle_free.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = ./ft_printf/libft
LIBFT = $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
TARGET = pipex

all: $(LIBFT) $(FT_PRINTF) $(TARGET)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBFT) $(FT_PRINTF)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	rm -f $(TARGET)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re