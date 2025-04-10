/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:56:43 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/10 19:06:52 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philos *p, t_data *data)
{
	pthread_mutex_lock(p->meal_lock);
	if (p->meals_eaten >= p->data->num_to_eat)
	{
		pthread_mutex_unlock(p->meal_lock);
		return (0);
	}
	if (current_time(1) - p->last_meal > p->data->time_to_die)
	{
		pthread_mutex_unlock(p->meal_lock);
		kill_all(data);
		msg_lock(p, 4);
		return (1);
	}
	pthread_mutex_unlock(p->meal_lock);
	return (0);
}

int	ft_is_dead(t_philos *p)
{
	int	death;

	death = 0;
	pthread_mutex_lock(p->dead_lock);
	if (p->dead == 1)
		death = p->dead;
	pthread_mutex_unlock(p->dead_lock);
	return (death);
}

void	kill_all(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		pthread_mutex_lock(p->philos[i].dead_lock);
		p->philos[i].dead = 1;
		pthread_mutex_unlock(p->philos[i].dead_lock);
		i++;
	}
}

int	check_meals(t_data *p)
{
	int	i;
	int	done;

	if (p->num_to_eat == -1)
		return (0);
	i = 0;
	done = 0;
	while (i < p->num_philos)
	{
		pthread_mutex_lock(p->philos[i].meal_lock);
		if (p->philos[i].meals_eaten >= p->num_to_eat)
			done++;
		pthread_mutex_unlock(p->philos[i].meal_lock);
		i++;
	}
	if (done == p->num_philos)
		return (1);
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
			if (check_death(&philos[i], p))
				return (NULL);
			i++;
		}
		if (check_meals(p))
		{
			kill_all(p);
			// meals_done(p);
			return (NULL);
		}
	}
	kill_all(p);
	return (NULL);
}
