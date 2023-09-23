/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:18:34 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/23 12:23:19 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->params.num_philosophers)
	{
		if (pthread_mutex_destroy(&program->forks[i]) != 0)
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