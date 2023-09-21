/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aajaanan <aajaanan@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 12:58:15 by aajaanan          #+#    #+#             */
/*   Updated: 2023/09/21 13:55:53 by aajaanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{

	return (arg);
}

void	*inspector(void *arg)
{
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