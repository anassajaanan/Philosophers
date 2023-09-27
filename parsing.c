/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:09:49 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/27 17:33:59 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_numeric_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_numeric(argv[i]))
		{
			ft_putstr_fd("Error: ", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putstr_fd(" is not a valid number\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	validate_args(t_params *params)
{
	if (params->num_philosophers > 200)
	{
		ft_putstr_fd("❌ Error: number_of_philosophers must be less than \
200 ❌ \n", STDERR_FILENO);
		return (1);
	}
	if (params->time_to_die < 60)
	{
		ft_putstr_fd("❌ Error: time_to_die must be greater than 60 ❌ \n",
			STDERR_FILENO);
		return (1);
	}
	if (params->time_to_eat < 60)
	{
		ft_putstr_fd("❌ Error: time_to_eat must be greater than 60 ❌ \n",
			STDERR_FILENO);
		return (1);
	}
	if (params->time_to_sleep < 60)
	{
		ft_putstr_fd("❌ Error: time_to_sleep must be greater than 60 ❌ \n",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	parse_command_line_args(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Usage: ", STDERR_FILENO);
		ft_putstr_fd(argv[0], STDERR_FILENO);
		ft_putstr_fd(" number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n", STDERR_FILENO);
		return (1);
	}
	if (!validate_numeric_args(argc, argv))
		return (1);
	params->num_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->num_times_to_eat = ft_atoi(argv[5]);
	else
		params->num_times_to_eat = -1;
	if (validate_args(params) != 0)
		return (1);
	return (0);
}
