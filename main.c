/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:15 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/21 16:49:40 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>

void	*routine(void *arg)
{

	return (arg);
}

int	is_philosopher_dead(t_program *program, t_philo *philo)
{
	int	time;
	
	pthread_mutex_lock(&program->meal_mutex);
	time = get_current_time() - philo->last_meal_time;
	if (time > program->params.time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(&program->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&program->meal_mutex);
	return (0);
}


int	check_dead_philosophers(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = program->philos;
	while (i < program->params.num_philosophers)
	{
		if (is_philosopher_dead(program, &philos[i]))
		{
			// print this philosopher died;
			pthread_mutex_lock(&program->death_mutex);
			program->dead_flag = 1;
			pthread_mutex_unlock(&program->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_philosophers_have_eaten(t_program *program)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = program->philos;
	while (i < program->params.num_philosophers)
	{
		pthread_mutex_lock(&program->meal_mutex);
		if (philos[i].meals_eaten < program->params.num_times_to_eat)
		{
			pthread_mutex_unlock(&program->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&program->meal_mutex);
		i++;
	}
	pthread_mutex_lock(&program->death_mutex);
	program->dead_flag = 1;
	pthread_mutex_unlock(&program->death_mutex);
	return (1);
}


void	*inspector(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (check_dead_philosophers(program) || all_philosophers_have_eaten(program))
			break;
	}
	return (arg);
}

int main(int argc, char **argv)
{
	t_program	program;

	if (parse_command_line_args(argc, argv, &program.params) != 0)
		return (1);
	
	if (init_program(&program) != 0)
		return (1);
	
	if (create_philosopher_threads(&program) != 0 
		|| create_inspector_thread(&program) != 0)
		return (1);
	
	
	if (join_philosopher_threads(&program) != 0 
		|| join_inspector_thread(&program) != 0)
		return (1);
	if (destroy_program(&program) != 0)
		return (1);
	return (0);
}
