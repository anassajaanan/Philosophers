/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:12:08 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 17:13:24 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_philosopher_dead(t_philo *philo)
{
	size_t	time;
	
	pthread_mutex_lock(philo->meal_mutex);
	time = get_current_time() - philo->last_meal_time;
	if (time > philo->params->time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

static int	check_dead_philosophers(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philosophers)
	{
		if (is_philosopher_dead(&philos[i]))
		{
			print_message(&philos[i], "died");
			pthread_mutex_lock(philos->death_mutex);
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	all_philosophers_have_eaten(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->params->num_times_to_eat == -1)
		return (0);
	while (i < philos->params->num_philosophers)
	{
		pthread_mutex_lock(philos->meal_mutex);
		if (philos[i].meals_eaten < philos->params->num_times_to_eat)
		{
			pthread_mutex_unlock(philos->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(philos->meal_mutex);
		i++;
	}
	pthread_mutex_lock(philos->death_mutex);
	*philos->dead_flag = 1;
	pthread_mutex_unlock(philos->death_mutex);
	return (1);
}


void	*inspector(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (check_dead_philosophers(philos) || all_philosophers_have_eaten(philos))
			break;
	}
	return (arg);
}
