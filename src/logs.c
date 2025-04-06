/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:35:18 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 04:03:46 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void    ft_eat(t_philos *p)
{
    pthread_mutex_lock(p->l_fork);
    ft_printf("%d %d has taken a fork\n", current_time(), p->id);
    pthread_mutex_lock(p->r_fork);
    ft_printf("%d %d has taken a fork\n", current_time(), p->id);
    ft_printf("%d %d is eating\n", current_time(), p->id);
    pthread_mutex_lock(p->meal_lock);
    p->last_meal = current_time();
    p->meals_eaten++;
    pthread_mutex_unlock(p->meal_lock);
    // ft_usleep(p->data->time_to_eat); fix this later
    pthread_mutex_unlock(p->l_fork);
    pthread_mutex_unlock(p->r_fork);
}

void    ft_sleep(t_philos *p)
{
    ft_printf("%d %d is sleeping\n", current_time(), p->id);
    // ft_usleep(p->data->time_to_sleep); fix this later
}

void    ft_think(t_philos *p)
{
    ft_printf("%d %d is thinking\n", current_time(), p->id);
}

void    ft_die(t_philos *p)
{
    ft_printf("%d %d died\n", current_time(), p->id);
    // Implement the logic for dying here
}
