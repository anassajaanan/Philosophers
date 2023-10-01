/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:30:07 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/01 18:33:29 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	sleep_and_think(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	print_message(philo, "is thinking");
}

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		sem_wait(philo->forks);
		print_message(philo, "has taken a fork");
		if (philo->num_philosophers == 1)
		{
			ft_usleep(philo->time_to_die);
			sem_post(philo->forks);
			exit(0);
		}
		sem_wait(philo->forks);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
		ft_usleep(philo->time_to_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		if (philo->num_times_to_eat != -1
			&& philo->meals_eaten >= philo->num_times_to_eat)
			exit(0);
		sleep_and_think(philo);
	}
}
