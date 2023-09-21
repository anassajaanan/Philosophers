/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_program.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:15:45 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/21 13:53:57 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <unistd.h>

static int	init_forks(t_fork *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		forks[i].id = i;
		forks[i].is_taken = 0;
		if (pthread_mutex_init(&forks[i].mutex, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_philosophers(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = program->philos;
	while (i < program->params.num_philosophers)
	{
		philos[i].id = i;
		philos[i].is_eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_current_time();
		philos[i].dead_flag = &program->dead_flag;
		i++;
	}
}

int	init_program(t_program *program)
{
	init_philosophers(program);
	program->dead_flag = 0;
	program->start_time = get_current_time();
	if (init_forks(program->forks, program->params.num_philosophers) != 0 
		|| pthread_mutex_init(&program->death_mutex, NULL) != 0 
		|| pthread_mutex_init(&program->meal_mutex, NULL) != 0 
		|| pthread_mutex_init(&program->output_mutex, NULL) != 0)
	{
		ft_putstr_fd("Error: failed to initialize mutex\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	destroy_program(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->params.num_philosophers)
	{
		if (pthread_mutex_destroy(&program->forks[i].mutex) != 0)
		{
			ft_putstr_fd("Error: failed to destroy mutex\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	if (pthread_mutex_destroy(&program->death_mutex) != 0
		|| pthread_mutex_destroy(&program->meal_mutex) != 0
		|| pthread_mutex_destroy(&program->output_mutex) != 0)
		{
			ft_putstr_fd("Error: failed to destroy mutex\n", STDERR_FILENO);
			return (1);
		}
	return (0);
}
