/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:04:02 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/10 18:24:17 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	error_msg(t_data *p, int error_code)
{
	if (error_code == 0)
		ft_printf("Error: Memory allocation failed\n");
	else if (error_code == 1)
	{
		ft_printf("Error: Invalid number of arguments\n");
		ft_printf("Program usage: ");
		ft_printf("./philosophers <num_philos> <time_to_die> <time_to_eat> ");
		ft_printf("<time_to_sleep> [num_to_eat]\n");
	}
	else if (error_code == 2)
		ft_printf("Error: Invalid argument values\n");
	else if (error_code == 3)
		ft_printf("Error: Mutex initialization failed\n");
	else if (error_code == 4)
		ft_printf("Error: Thread creation failed\n");
	free_philos(p);
	exit(1);
}

void	free_philos(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		pthread_mutex_destroy(&p->forks[i]);
		pthread_mutex_destroy(p->philos[i].write_lock);
		pthread_mutex_destroy(p->philos[i].meal_lock);
		pthread_mutex_destroy(p->philos[i].dead_lock);
		free(p->philos[i].meal_lock);
		free(p->philos[i].dead_lock);
		free(p->philos[i].write_lock);
		i++;
	}
	free(p->thread);
	free(p->philos);
	free(p->forks);
	free(p);
}
