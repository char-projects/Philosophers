/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:56:43 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 14:02:59 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int check_death(t_philos *p)
{
    pthread_mutex_lock(p->meal_lock);
    if (current_time() - p->last_meal > p->data->time_to_die)
    {
        pthread_mutex_unlock(p->meal_lock);
        pthread_mutex_lock(p->dead_lock);
        p->died = 1;
        pthread_mutex_unlock(p->dead_lock);
        msg_lock(p, 4);
        return (1);
    }
    pthread_mutex_unlock(p->meal_lock);
    return (0);
}
