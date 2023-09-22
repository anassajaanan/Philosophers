/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:05:25 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/21 17:40:39 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	create_philosopher_threads(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = program->philos;
	while (i < program->params.num_philosophers)
	{
		if (pthread_create(&philos[i].thread, NULL, &routine, &philos[i]) != 0)
		{
			ft_putstr_fd("Error: failed to create thread\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	create_inspector_thread(t_program *program)
{
	if (pthread_create(&program->inspector, NULL, &inspector, program) != 0)
	{
		ft_putstr_fd("Error: failed to create thread\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	join_philosopher_threads(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = program->philos;
	while (i < program->params.num_philosophers)
	{
		if (pthread_join(philos[i].thread, NULL) != 0)
		{
			ft_putstr_fd("Error: failed to join thread\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_inspector_thread(t_program *program)
{
	if (pthread_join(program->inspector, NULL) != 0)
	{
		ft_putstr_fd("Error: failed to join thread\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}