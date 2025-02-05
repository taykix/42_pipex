NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

BONUS_SRCS = $(wildcard *_bonus.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

HEADERS = libft.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus


