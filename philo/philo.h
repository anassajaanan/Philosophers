/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:55:46 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 19:00:38 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_NUM_PHILOSOPHERS 200

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
	t_params		*params;

	int				is_eating;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			start_time;

	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	int				*dead_flag;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*output_mutex;
}					t_philo;

typedef struct s_program
{
	t_params		params;
	pthread_t		inspector_thread;
	t_philo			philos[MAX_NUM_PHILOSOPHERS];
	pthread_mutex_t	forks[MAX_NUM_PHILOSOPHERS];

	int				dead_flag;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	output_mutex;
}					t_program;

// #====================# parsing.c #====================#
int					parse_command_line_args(int argc, char **argv,
						t_params *params);

// #====================# philo_init.c #====================#
int					init_program(t_program *program);

// #====================# thread_management.c #====================#
int					create_philosopher_threads(t_philo *philos);
int					create_inspector_thread(t_program *program);
int					join_philosopher_threads(t_philo *philos);
int					join_inspector_thread(pthread_t inspector_thread);

// #====================# routine.c #====================#
void				*routine(void *arg);

// #====================# inspector.c #====================#
void				*inspector(void *arg);

// #====================# philo_destroy.c #====================#
int					destroy_mutexes(t_program *program);

// #====================# utils.c #====================#
int					is_numeric(const char *str);
void				ft_putstr_fd(char *s, int fd);
long				ft_atoi(const char *str);
size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);
int					philosophers_are_alive(t_philo *philo);
void				print_message(t_philo *philo, char *message);

#endif /* PHILO_H */