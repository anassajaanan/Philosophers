/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 09:48:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/01 10:36:00 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>


typedef struct params
{
	int				num_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;
}					t_params;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	
	int				num_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;

	size_t			start_time;
	size_t			last_meal_time;
	int				meals_eaten;
	
	sem_t			*forks;
	sem_t			*output;
	sem_t			*death;
}					t_philo;


// #=================# parsing.c #=================#
int	parse_command_line_args(int argc, char **argv, t_philo *philo);

// #=================# philo_init.c #=================#
void	init_semaphores(t_philo *philo);

// #=================# philo.c #=================#
void	print_message(t_philo *philo, char *message);
void	*inspector(void *arg);

// #=================# utils.c #=================#
int					is_numeric(const char *str);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);


#endif /* PHILO_H */