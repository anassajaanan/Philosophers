NAME =		philo

SRCS =		main.c \
			parsing.c \
			init_destroy.c \
			thread_management.c \
			utils.c \

OBJS =		$(SRCS:.c=.o)

CC	 =		gcc
# CFLAGS =	-Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
CFLAGS =	-g3 -pthread -fsanitize=thread


all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean 
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean