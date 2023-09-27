NAME =		philo

SRCS =		philo.c \
			parsing.c \
			philo_init.c \
			philo_destroy.c \
			thread_management.c \
			utils.c \

OBJS =		$(SRCS:.c=.o)

CC	 =		cc
# CFLAGS =	-Wall -Wextra -Werror -pthread -g3 -fsanitize=thread
CFLAGS =	-Wall -Wextra -Werror


all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean 
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean