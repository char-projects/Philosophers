/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:56:43 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/08 00:58:03 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philos *p)
{
	pthread_mutex_lock(p->meal_lock);
	if (current_time() - p->last_meal > p->data->time_to_die)
	{
		pthread_mutex_unlock(p->meal_lock);
		pthread_mutex_lock(p->dead_lock);
		p->died = 1;
		ft_die(p);
		pthread_mutex_unlock(p->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(p->meal_lock);
	return (0);
}

int	check_meals(t_philos *p)
{
	int	i;
	int	done;

	if (!p || !p[0].data || p->data->num_to_eat == -1)
		return (1);
	i = 0;
	done = 0;
	while (i < p[0].data->num_philos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (p[i].meals_eaten >= p[0].data->num_to_eat)
		{
			msg_lock(p, 5);
			done++;
		}
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	if (done == p->data->num_philos)
	{
		pthread_mutex_lock(p[0].dead_lock);
		p->died = 1;
		pthread_mutex_unlock(p[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *tmp_p)
{
	t_data		*p;
	t_philos	*philos;
	int			i;

	p = (t_data *)tmp_p;
	philos = p->philos;
	while (1)
	{
		i = 0;
		while (i < p->num_philos)
		{
			if (check_death(&philos[i]))
				return (NULL);
			i++;
		}
		if (check_meals(philos))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
