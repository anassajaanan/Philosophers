/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:52:26 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/30 15:39:40 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	init_semaphores(t_philo *philo)
{
	unlink("fork");
	unlink("output");
	unlink("death");
	philo->fork = sem_open("fork", O_CREAT, 0644, philo->num_philosophers);
	philo->output = sem_open("output", O_CREAT, 0644, 1);
	philo->death = sem_open("death", O_CREAT, 0644, 1);
}


void	print_message(t_philo *philo, char *message)
{
	sem_wait(philo->output);
	printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id, message);
	sem_post(philo->output);
}

void	*monitoring(void *arg)
{
	t_philo *philo;

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

void	routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		sem_wait(philo->fork);
		print_message(philo, "has taken a fork");
		if (philo->num_philosophers == 1)
		{
			ft_usleep(philo->time_to_die);
			sem_post(philo->fork);
			exit(0);
		}
		sem_wait(philo->fork);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		philo->last_meal_time = get_current_time();
		philo->meals_eaten++;
		ft_usleep(philo->time_to_eat);
		sem_post(philo->fork);
		sem_post(philo->fork);

		if (philo->num_times_to_eat != -1 && philo->meals_eaten >= philo->num_times_to_eat)
			exit(0);
		
		print_message(philo, "is sleeping");
		ft_usleep(philo->time_to_sleep);

		print_message(philo, "is thinking");
	}
}

int	child(t_philo *philo)
{
	philo->id += 1;
	philo->last_meal_time = get_current_time();
	philo->meals_eaten = 0;
	if (pthread_create(&philo->thread, NULL, &monitoring, philo))
		return (1);
	pthread_detach(philo->thread);
	routine(philo);
	return (0);
}

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

int	create_philosophers(t_philo *philo)
{
	int		i;
	pid_t	*pid;

	i = 0;
	pid = (pid_t *)malloc(sizeof(pid_t) * philo->num_philosophers);
	if (pid == NULL)
		return (1);
	philo->start_time = get_current_time();
	while (i < philo->num_philosophers)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (1);
		if (pid[i] == 0)
		{
			philo->id = i;
			break;
		}
		i++;
		usleep(100);
	}
	if (pid[philo->id] == 0 && !child(philo))
		return (1);
	else
		parent(philo, pid);
	free(pid);
	exit(0);
}


int main(int argc, char **argv)
{
	t_philo philo;

	if (parse_command_line_args(argc, argv, &philo) != 0)
		return (1);
	init_semaphores(&philo);
	create_philosophers(&philo);
}