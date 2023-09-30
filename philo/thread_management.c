/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:09:27 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 18:53:14 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			ft_putstr_fd("❌ Error: failed to create thread ❌ \n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_inspector_thread(t_program *program)
{
	if (pthread_create(&program->inspector_thread, NULL, &inspector,
			program->philos) != 0)
	{
		ft_putstr_fd("❌ Error: failed to create thread ❌ \n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	join_philosopher_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			ft_putstr_fd("❌ Error: failed to join thread ❌ \n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_inspector_thread(pthread_t inspector_thread)
{
	if (pthread_join(inspector_thread, NULL) != 0)
	{
		ft_putstr_fd("❌ Error: failed to join inspector thread ❌ \n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}
