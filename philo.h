/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:17:01 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/21 09:44:25 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_PHILOS 200

typedef struct s_params
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
	
	pthread_mutex_t	mutex;
}					t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			start_time;
	
	int				num_philosophers;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_times_to_eat;

	t_fork			*left_fork;
	t_fork			*right_fork;
	t_fork			*forks;

	int				*dead_flag;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*write_lock;
}					t_philo;

typedef struct s_program
{
	t_philo			*philos;
	t_fork			*forks;
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_program;

// #====================# parsing.c #====================#
int	parse_command_line_args(int argc, char **argv, t_params *params);

// #====================# philo_init.c #====================#
void	init_program(t_program *program, t_philo *philos, t_fork *forks);
void	init_philos(t_program *program, t_params *params, t_philo *philos, t_fork *forks);
void	init_forks(t_params *params, t_fork *forks);

// #====================# utils.c #====================#
int		is_numeric(const char *str);
void	ft_putstr_fd(char *s, int fd);
long	ft_atoi(const char *str);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif /* PHILO_H */