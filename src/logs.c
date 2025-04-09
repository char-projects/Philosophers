/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:35:18 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/09 02:27:26 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_eat(t_philos *p)
{
    if (check_death(p) == 0)
    {
        if (pthread_mutex_lock(p->l_fork) != 0)
            return ;
        msg_lock(p, 0);
        if (pthread_mutex_lock(p->r_fork) != 0)
        {
            pthread_mutex_unlock(p->l_fork);
            return ;
        }
        msg_lock(p, 0);
        msg_lock(p, 1);
        pthread_mutex_lock(p->meal_lock);
        p->last_meal = current_time(1);
        p->meals_eaten++;
        pthread_mutex_unlock(p->meal_lock);
        ft_usleep(p->data->time_to_eat);
        pthread_mutex_unlock(p->l_fork);
        pthread_mutex_unlock(p->r_fork);
    }
}

void	ft_sleep(t_philos *p)
{
	msg_lock(p, 2);
	ft_usleep(p->data->time_to_sleep);
}
