/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:48:10 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/30 11:59:02 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>


typedef struct s_philo
{
	int			id;
	pthread_t	thread;

	int			num_philosophers;
	size_t		time_to_die;
	size_t		time_to_eat;
	size_t		time_to_sleep;
	int			num_times_to_eat;

	int			meals_eaten;
	size_t		start_time;
	size_t		last_meal_time;

	sem_t		*fork;
	sem_t		*output;
	sem_t		*death;
	
}			t_philo;



// #====================# utils.c #====================#
int					is_numeric(const char *str);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);

// #====================# parsing.c #====================#
int	parse_command_line_args(int argc, char **argv, t_philo *philo);


#endif /* PHILO_H */