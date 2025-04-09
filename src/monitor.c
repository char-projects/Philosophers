/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:56:43 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/09 01:58:21 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_death(t_philos *p)
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
		return (1);
	}
	pthread_mutex_unlock(p->meal_lock);
	return (0);
}

int	check_meals(t_philos *p)
{
	int	i;
	int	done;

	if (p[0].data->num_to_eat == -1)
		return (0);
	i = 0;
	done = 0;
	while (i < p[0].data->num_philos)
	{
		pthread_mutex_lock(p[i].meal_lock);
		if (p[i].meals_eaten >= p[0].data->num_to_eat)
			done++;
		pthread_mutex_unlock(p[i].meal_lock);
		i++;
	}
	if (done == p->data->num_philos)
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
	while (!p->dead)
	{
		i = 0;
		while (i < p->num_philos)
		{
			if (check_death(&philos[i]))
            {
                pthread_mutex_lock(philos[i].dead_lock);
				p->dead = 1;
                pthread_mutex_unlock(philos[i].dead_lock);
				ft_is_dead(&philos[i]);
				msg_lock(&philos[i], 4);
                return (NULL);
            }
            i++;
		}
		if (check_meals(philos))
        {
			pthread_mutex_lock(philos[0].dead_lock);
            p->dead = 1;
            pthread_mutex_unlock(philos[0].dead_lock);
			ft_is_dead(&philos[0]);
			pthread_mutex_lock(philos[0].write_lock);
			ft_printf("All philosophers have finished their meals. Simulation ending\n");
			pthread_mutex_unlock(philos[0].write_lock);
            return (NULL);
        }
	}
	return (NULL);
}
