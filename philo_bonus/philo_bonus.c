/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 09:53:44 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/02 08:34:24 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	parent(t_philo *philo, pid_t *pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->num_philosophers)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < philo->num_philosophers)
			{
				kill(pid[i], SIGKILL);
				i++;
			}
		}
		i++;
	}
}

int	child(t_philo *philo)
{
	philo->id += 1;
	philo->last_meal_time = get_current_time();
	philo->meals_eaten = 0;
	if (pthread_create(&philo->thread, NULL, &inspector, philo))
		return (1);
	pthread_detach(philo->thread);
	routine(philo);
	return (0);
}

int	create_philosophers(t_philo *philo)
{
	int		i;
	pid_t	pid[200];

	i = 0;
	philo->start_time = get_current_time();
	while (i < philo->num_philosophers)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		else if (pid[i] == 0)
		{
			philo->id = i;
			break ;
		}
		i++;
	}
	if (pid[philo->id] == 0 && !child(philo))
		return (1);
	else
		parent(philo, pid);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	philo;

	if (parse_command_line_args(argc, argv, &philo) != 0)
		return (1);
	init_semaphores(&philo);
	create_philosophers(&philo);
}
