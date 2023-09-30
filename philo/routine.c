/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 17:05:01 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 18:56:43 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	if (philo->params->num_philosophers == 1)
	{
		ft_usleep(philo->params->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	philo->is_eating = 1;
	print_message(philo, "is eating");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_meal_time = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_mutex);
	ft_usleep(philo->params->time_to_eat);
	philo->is_eating = 0;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	sleep_and_think(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->params->time_to_sleep);
	print_message(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->params->time_to_eat);
	while (philosophers_are_alive(philo))
	{
		eat(philo);
		sleep_and_think(philo);
	}
	return (arg);
}
