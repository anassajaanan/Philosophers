/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:12:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 18:57:27 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philosophers_are_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (*philo->dead_flag == 1)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (1);
}

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->output_mutex);
	if (philosophers_are_alive(philo))
	{
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
			message);
	}
	pthread_mutex_unlock(philo->output_mutex);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (parse_command_line_args(argc, argv, &program.params) != 0)
		return (1);
	if (init_program(&program) != 0)
		return (1);
	if (create_inspector_thread(&program) != 0
		|| create_philosopher_threads(program.philos) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}
	if (join_inspector_thread(program.inspector_thread) != 0
		|| join_philosopher_threads(program.philos) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}
	destroy_mutexes(&program);
	return (0);
}
