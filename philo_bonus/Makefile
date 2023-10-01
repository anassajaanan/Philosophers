NAME =		philo_bonus

SRCS =		philo.c \
			parsing.c \
			philo_init.c \
			inspector.c \
			utils.c \

OBJS =		$(SRCS:.c=.o)

CC	 =		cc
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