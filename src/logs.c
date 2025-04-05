/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 18:35:18 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/05 18:43:03 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void    ft_take_fork(t_philos *p)
{
    ft_printf("%d %d has taken a fork\n", 0, p->id);
    // Implement the logic for taking a fork here
}

void    ft_eat(t_philos *p)
{
    ft_printf("%d %d is eating\n", 0, p->id);
    // Implement the eating logic here
}

void    ft_sleep(t_philos *p)
{
    ft_printf("%d %d is sleeping\n", 0, p->id);
    // Implement the sleeping logic here
}

void    ft_think(t_philos *p)
{
    ft_printf("%d %d is thinking\n", 0, p->id);
    // Implement the thinking logic here
}

void    ft_die(t_philos *p)
{
    ft_printf("%d %d died\n", 0, p->id);
    // Implement the logic for dying here
}
