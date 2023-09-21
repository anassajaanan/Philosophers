/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:40:55 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/20 08:41:57 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_program *program, t_philo *philos, t_fork *forks)
{
	program->philos = philos;
	program->forks = forks;
	program->dead_flag = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
}

void	init_philos(t_program *program, t_params *params, t_philo *philos, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < params->num_philosophers)
	{
		philos[i].id = i;

		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].start_time = get_current_time();
		
		philos[i].num_philosophers = params->num_philosophers;
		philos[i].time_to_die = params->time_to_die;
		philos[i].time_to_eat = params->time_to_eat;
		philos[i].time_to_sleep = params->time_to_sleep;
		philos[i].num_times_to_eat = params->num_times_to_eat;

		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % params->num_philosophers];
		philos[i].forks = forks;

		philos[i].dead_flag = &program->dead_flag;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].write_lock = &program->write_lock;
		i++;
	}
}

void	init_forks(t_params *params, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < params->num_philosophers)
	{
		forks[i].id = i;
		pthread_mutex_init(&forks[i].mutex, NULL);
		i++;
	}
}
