NAME =		philo_bonus

SRCS =		philo_bonus.c \
			parsing_bonus.c \
			philo_init_bonus.c \
			inspector_bonus.c \
			routine_bonus.c \
			utils_bonus.c \

OBJS =		$(SRCS:.c=.o)

CC	 =		cc
CFLAGS =	-Wall -Wextra -Werror -pthread


all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean 
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean