/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:12:23 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 10:30:52 by aajaanan         ###   ########.fr       */
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

int	is_philosopher_dead(t_philo *philo)
{
	int	time;
	
	pthread_mutex_lock(philo->meal_mutex);
	time = get_current_time() - philo->last_meal_time;
	if (time > philo->params->time_to_die && philo->is_eating == 0)
	{
		pthread_mutex_unlock(philo->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_mutex);
	return (0);
}

int	check_dead_philosophers(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->params->num_philosophers)
	{
		if (is_philosopher_dead(&philos[i]))
		{
			print_message(&philos[i], "died");
			pthread_mutex_lock(philos->death_mutex);
			*philos->dead_flag = 1;
			pthread_mutex_unlock(philos->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_philosophers_have_eaten(t_philo *philos)
{
	int	i;

	i = 0;
	if (philos->params->num_times_to_eat == -1)
		return (0);
	while (i < philos->params->num_philosophers)
	{
		pthread_mutex_lock(philos->meal_mutex);
		if (philos[i].meals_eaten < philos->params->num_times_to_eat)
		{
			pthread_mutex_unlock(philos->meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(philos->meal_mutex);
		i++;
	}
	pthread_mutex_lock(philos->death_mutex);
	*philos->dead_flag = 1;
	pthread_mutex_unlock(philos->death_mutex);
	return (1);
}


void	*inspector(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (1)
	{
		if (check_dead_philosophers(program->philos) || all_philosophers_have_eaten(program->philos))
		{
			break;
		}
	}
	return (arg);
}

// void	*routine(void *arg)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)arg;

	// if (philo->id % 2 == 0)
	// 	ft_usleep(philo->params->time_to_eat);
	
// 	while (philosophers_are_alive(philo))
// 	{
// 		pthread_mutex_lock(philo->left_fork);
// 		print_message(philo, "has taken a fork");

// 		if (philo->params->num_philosophers == 1)
// 		{
// 			ft_usleep(philo->params->time_to_die);
// 			pthread_mutex_unlock(philo->left_fork);
// 			return (arg);
// 		}
// 		pthread_mutex_lock(philo->right_fork);
// 		print_message(philo, "has taken a fork");
// 		philo->is_eating = 1;
// 		print_message(philo, "is eating");
// 		pthread_mutex_lock(philo->meal_mutex);
// 		philo->last_meal_time = get_current_time();
// 		philo->meals_eaten++;
// 		pthread_mutex_unlock(philo->meal_mutex);
// 		ft_usleep(philo->params->time_to_eat);

// 		philo->is_eating = 0;
// 		pthread_mutex_unlock(philo->right_fork);
// 		pthread_mutex_unlock(philo->left_fork);	
// 		// Sleeping
// 		print_message(philo, "is sleeping");
// 		ft_usleep(philo->params->time_to_sleep);

// 		// Thinking
// 		print_message(philo, "is thinking");

// 	}
	
// 	return (arg);
// }


int	get_fork_owner(t_philo *philo, t_fork *fork)
{
	int owner_id;

	pthread_mutex_lock(philo->owner_mutex);
	owner_id = fork->owner_id;
	pthread_mutex_unlock(philo->owner_mutex);
	return (owner_id);
}



void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(philo->params->time_to_eat);

	while (philosophers_are_alive(philo))
	{
		
		pthread_mutex_lock(&philo->left_fork->mutex);
		if (philo->left_fork->is_taken == 0)
		{
			philo->left_fork->is_taken = 1;
			philo->left_fork->owner_id = philo->id;
			if (philo->params->num_philosophers == 1)
			{
				print_message(philo, "has taken a fork");
				ft_usleep(philo->params->time_to_die);
				pthread_mutex_unlock(&philo->left_fork->mutex);
				return (arg);
			}
			// print_message(philo, "has taken a fork");
		}
		pthread_mutex_unlock(&philo->left_fork->mutex);
		
		pthread_mutex_lock(&philo->right_fork->mutex);
		if (philo->right_fork->is_taken == 0)
		{
			philo->right_fork->is_taken = 1;
			philo->right_fork->owner_id = philo->id;
			// print_message(philo, "has taken a fork");
		}
		pthread_mutex_unlock(&philo->right_fork->mutex);

		// if (philo->left_fork->owner_id == philo->id && philo->right_fork->owner_id == philo->id)
		if (get_fork_owner(philo, philo->left_fork) == philo->id && get_fork_owner(philo, philo->right_fork) == philo->id)
		{
			print_message(philo, "has taken a fork");
			print_message(philo, "has taken a fork");
			philo->is_eating = 1;
			print_message(philo, "is eating");
			pthread_mutex_lock(philo->meal_mutex);
			philo->last_meal_time = get_current_time();
			philo->meals_eaten++;
			pthread_mutex_unlock(philo->meal_mutex);
			ft_usleep(philo->params->time_to_eat);
			philo->is_eating = 0;
			pthread_mutex_lock(&philo->left_fork->mutex);
			philo->left_fork->is_taken = 0;
			pthread_mutex_unlock(&philo->left_fork->mutex);
			pthread_mutex_lock(&philo->right_fork->mutex);
			philo->right_fork->is_taken = 0;
			pthread_mutex_unlock(&philo->right_fork->mutex);

			// Sleeping
			print_message(philo, "is sleeping");
			ft_usleep(philo->params->time_to_sleep);

			// Thinking
			print_message(philo, "is thinking");
		}
		
		


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
	
	if (create_philosopher_threads(program.philos) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}
	if (create_inspector_thread(&program) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}

	if (join_philosopher_threads(program.philos) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}

	if (join_inspector_thread(program.inspector_thread) != 0)
	{
		destroy_mutexes(&program);
		return (1);
	}
	
	destroy_mutexes(&program);
	return (0);
}