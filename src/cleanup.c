/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:04:02 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/20 17:49:29 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	error_msg(t_data *p, int error_code)
{
	if (error_code == 0)
		printf("Error: Memory allocation failed\n");
	else if (error_code == 1)
	{
		printf("Error: Invalid number of arguments\n");
		printf("Program usage: ");
		printf("./philosophers <num_philos> <time_to_die> <time_to_eat> ");
		printf("<time_to_sleep> [num_to_eat]\n");
	}
	else if (error_code == 2)
		printf("Error: Invalid argument values\n");
	else if (error_code == 3)
		printf("Error: Mutex initialization failed\n");
	else if (error_code == 4)
		printf("Error: Thread creation failed\n");
	free_philos(p);
	return (-1);
}

void	msg_lock(t_philos *p, int code)
{
	char	*str;

	if (code == 0)
		str = "has taken a fork";
	else if (code == 1)
		str = "is eating";
	else if (code == 2)
		str = "is sleeping";
	else if (code == 3)
		str = "is thinking";
	else if (code == 4)
		str = "died";
	else if (code == 5)
		str = "is dead in main";
	else
		return ;
	pthread_mutex_lock(p->write_lock);
	printf("%zu %d %s\n", current_time(1), p->id, str);
	pthread_mutex_unlock(p->write_lock);
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
