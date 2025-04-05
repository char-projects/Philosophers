/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:29:46 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/05 19:20:51 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_argv(int argc, char **argv, t_data *p)
{
	p->num_philos = ft_atoi(argv[1]);
	p->time_to_die = ft_atoi(argv[2]);
	p->time_to_eat = ft_atoi(argv[3]);
	p->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		p->num_to_eat = ft_atoi(argv[5]);
	else
		p->num_to_eat = -1; // No limit on eating
	p->dead = 0;
	if (p->num_philos <= 0 || p->time_to_die <= 0 || p->time_to_eat <= 0
		|| p->time_to_sleep <= 0 || (argc == 6 && p->num_to_eat <= 0))
		error_msg(p, 2);
}

void	init_philos(t_data *p)
{
	int	i;

	i = 0;
	p->philos = malloc(sizeof(t_philos) * (p->num_philos + 1));
	if (!p->philos)
		error_msg(p, 0);
	while (i < p->num_philos)
	{
		p->philos[i].id = i + 1;
		p->philos[i].meals_eaten = 0;
		p->philos[i].last_meal = 0;
		p->philos[i].died = 0;
		/* Not sure about this part
		if (i % 2 == 0)
			p->philos[i].l_fork = &p->philos[i - 1].r_fork;
		else
			p->philos[i].l_fork = &p->philos[i + 1].r_fork;
		*/
		i++;
	}
}

void	init_forks(t_data *p)
{
	int	i;

	i = 0;
	p->forks = malloc(sizeof(pthread_mutex_t) * (p->num_philos));
	if (!p->forks)
		error_msg(p, 0);
	while (i < p->num_philos)
	{
		if (pthread_mutex_init(&p->forks[i], NULL) != 0)
			error_msg(p, 3);
		i++;
	}
}
