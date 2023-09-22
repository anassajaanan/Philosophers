/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:55:46 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/22 09:48:26 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stddef.h>
#include <sys/_pthread/_pthread_mutex_t.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_NUM_PHILOSOPHERS 200

typedef struct params
{
	int		num_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		num_times_to_eat;
}			t_params;

typedef struct s_fork
{
	int				id;
	int				is_taken;
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	t_fork			*forks;
	struct s_philo	*philos;
	t_params		*params;
	int				is_eating;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			start_time;
	int				*dead_flag;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*meal_mutex;
	pthread_mutex_t	*output_mutex;
}				t_philo;

typedef struct s_program
{
	pthread_t		inspector;
	t_params		params;
	t_fork			forks[MAX_NUM_PHILOSOPHERS];
	t_philo			philos[MAX_NUM_PHILOSOPHERS];
	int				dead_flag;
	size_t			start_time;
	pthread_mutex_t	death_mutex;
    pthread_mutex_t	meal_mutex;
    pthread_mutex_t	output_mutex;
}					t_program;


void	*routine(void *arg);
void	*inspector(void *arg);

// #====================# parsing.c #====================#
int	parse_command_line_args(int argc, char **argv, t_params *params);

// #====================# init_destroy.c #====================#
int	init_program(t_program *program);
int	destroy_program(t_program *program);

// #====================# thread_management.c #====================#
int	create_philosopher_threads(t_program *program);
int	create_inspector_thread(t_program *program);
int	join_philosopher_threads(t_program *program);
int	join_inspector_thread(t_program *program);


// #====================# utils.c #====================#
int		is_numeric(const char *str);
void	ft_putstr_fd(char *s, int fd);
long	ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif /* PHILO_H */