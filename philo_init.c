/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:14:13 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/23 12:23:49 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(pthread_mutex_t *forks, int num_philosophers)
{
	int	i;

	i = 0;
	while (i < num_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error: Failed to initialize mutex\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}


static int	init_philosophers(t_program *program)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	t_params		*params;

	i = 0;
	philos = program->philos;
	forks = program->forks;
	params = &program->params;
	while (i < params->num_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].params = params;
		philos[i].is_eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_current_time();
		philos[i].start_time = get_current_time();
		
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % params->num_philosophers];

		philos[i].dead_flag = &program->dead_flag;
		philos[i].death_mutex = &program->death_mutex;
		philos[i].meal_mutex = &program->meal_mutex;
		philos[i].output_mutex = &program->output_mutex;
		i++;	
	}
	return (0);
}

int	init_program(t_program *program)
{
	init_forks(program->forks, program->params.num_philosophers);
	init_philosophers(program);
	program->dead_flag = 0;
	pthread_mutex_init(&program->death_mutex, NULL);
	pthread_mutex_init(&program->meal_mutex, NULL);
	pthread_mutex_init(&program->output_mutex, NULL);
	return (0);
}