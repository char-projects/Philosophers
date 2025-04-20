/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:29:46 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/20 18:18:13 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	init_argv(int argc, char **argv, t_data *p)
{
	int		i;
	size_t	num;

	i = 0;
	num = 0;
	while (++i < argc)
	{
		num = ft_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > 200))
			return (error_msg(p, 2));
		else if (i == 5 && ((int)num < 0 || num > INT_MAX))
			return (error_msg(p, 2));
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			return (error_msg(p, 2));
	}
	p->num_philos = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->num_to_eat = ft_atoi(argv[5]);
	else
		p->num_to_eat = -1;
	return (0);
}

int	init_forks(t_data *p)
{
	int	i;

	p->forks = malloc(sizeof(pthread_mutex_t) * p->num_philos);
	if (!p->forks)
		return (error_msg(p, 0));
	i = 0;
	while (i < p->num_philos)
	{
		pthread_mutex_init(&p->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_data *p)
{
	int	i;

	i = 0;
	p->philos = malloc(sizeof(t_philos) * p->num_philos);
	if (!p->philos)
		return (error_msg(p, 0));
	while (i < p->num_philos)
	{
		p->philos[i].id = i + 1;
		p->philos[i].meals_eaten = 0;
		p->philos[i].last_meal = current_time(1);
		p->philos[i].data = p;
		p->philos[i].dead = 0;
		p->philos[i].meal_lock = malloc(sizeof(pthread_mutex_t));
		p->philos[i].dead_lock = malloc(sizeof(pthread_mutex_t));
		p->philos[i].write_lock = malloc(sizeof(pthread_mutex_t));
		if (!p->philos[i].meal_lock || !p->philos[i].dead_lock
			|| !p->philos[i].write_lock)
			return (error_msg(p, 0));
		pthread_mutex_init(p->philos[i].meal_lock, NULL);
		pthread_mutex_init(p->philos[i].dead_lock, NULL);
		pthread_mutex_init(p->philos[i].write_lock, NULL);
		i++;
	}
	return (0);
}

void	distribute_forks(t_data *p)
{
	int	i;

	i = 0;
	while (i < p->num_philos)
	{
		if (i % 2 == 0)
		{
			p->philos[i].l_fork = &p->forks[i];
			p->philos[i].r_fork = &p->forks[(i + 1) % p->num_philos];
		}
		else
		{
			p->philos[i].l_fork = &p->forks[(i + 1) % p->num_philos];
			p->philos[i].r_fork = &p->forks[i];
		}
		i++;
	}
}
