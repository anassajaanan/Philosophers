/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:15 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/22 10:35:48 by aajaanan         ###   ########.fr       */
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
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id + 1, message);
	}
	pthread_mutex_unlock(philo->output_mutex);
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
			print_message(&philos[i], "died");
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
	if (program->params.num_times_to_eat == -1)
		return (0);
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
		{
			break;
		}
	}
	return (arg);
}

void	*routine(void *arg)
{
	int			i;
	t_philo		*philo;
	t_fork		*forks;
	t_params	*params;

	philo = (t_philo *)arg;
	forks = philo->forks;
	params = philo->params;
	// if (philo->id % 2 == 0)
	// 	ft_usleep(2);
	while (philosophers_are_alive(philo))
	{
		pthread_mutex_lock(&forks[(philo->id + (philo->id % 2)) % params->num_philosophers].mutex);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&forks[(philo->id + ((philo->id + 1) % 2)) % params->num_philosophers].mutex);
		print_message(philo, "has taken a fork");
		
		philo->is_eating = 1;
		pthread_mutex_lock(philo->meal_mutex);
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->meal_mutex);
		print_message(philo, "is eating");
		ft_usleep(params->time_to_eat);

		philo->is_eating = 0;
		pthread_mutex_unlock(&forks[(philo->id + (philo->id % 2)) % params->num_philosophers].mutex);
		pthread_mutex_unlock(&forks[(philo->id + ((philo->id + 1) % 2)) % params->num_philosophers].mutex);

		// Sleeping
		print_message(philo, "is sleeping");
		ft_usleep(params->time_to_sleep);

		// Thinking
		print_message(philo, "is thinking");

	}
	
	return (arg);
}

int main(int argc, char **argv)
{
	t_program	program;

	if (parse_command_line_args(argc, argv, &program.params) != 0)
		return (1);
	
	// if (init_program(&program) != 0)
	// 	return (1);
	
	// if (create_philosopher_threads(&program) != 0 
	// 	|| create_inspector_thread(&program) != 0)
	// 	return (1);
	
	
	// if (join_philosopher_threads(&program) != 0 
	// 	|| join_inspector_thread(&program) != 0)
	// 	return (1);
	// if (destroy_program(&program) != 0)
	// 	return (1);

	init_program(&program);
	create_philosopher_threads(&program);
	create_inspector_thread(&program);
	join_philosopher_threads(&program);
	join_inspector_thread(&program);
	destroy_program(&program);

	
	return (0);
}
