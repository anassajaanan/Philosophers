/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 10:31:39 by aajaanan          #+#    #+#             */
/*   Updated: 2023/10/01 10:31:54 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_semaphores(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("output");
	sem_unlink("death");
	philo->forks = sem_open("forks", O_CREAT, 0644, philo->num_philosophers);
	philo->output = sem_open("output", O_CREAT, 0644, 1);
	philo->death = sem_open("death", O_CREAT, 0644, 1);
}
