/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:34:59 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/02 08:10:16 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_message(t_philo *philo, char *message)
{
	sem_wait(philo->output);
	printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
		message);
	sem_post(philo->output);
}

void	*inspector(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->death);
		if (get_current_time() - philo->last_meal_time >= philo->time_to_die)
		{
			print_message(philo, "died");
			exit(1);
		}
		sem_post(philo->death);
		usleep(100);
	}
}
