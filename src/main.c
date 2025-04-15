/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/15 15:33:11 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Run with valgrind --tool=drd to check for data races

#include "../include/philosophers.h"

void	*ft_state(void *tmp_p)
{
	t_philos	*p;

	p = (t_philos *)tmp_p;
	if (p->id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (!ft_is_dead(p))
			ft_eat(p);
		else
			break ;
		if (!ft_is_dead(p))
		{
			msg_lock(p, 2);
			ft_usleep(p->data->time_to_sleep);
		}
		else
			break ;
		if (!ft_is_dead(p))
			msg_lock(p, 3);
		else
			break ;
	}
	return (NULL);
}

void	start_simulation(t_data *p)
{
	int			i;
	pthread_t	monitor_thread;

	p->thread = malloc(sizeof(pthread_t) * p->num_philos);
	if (!p->thread)
		error_msg(p, 0);
	if (pthread_create(&monitor_thread, NULL, monitor, (void *)p))
		error_msg(p, 4);
	i = 0;
	while (i < p->num_philos)
	{
		if (pthread_create(&p->thread[i], NULL, ft_state,
				(void *)&p->philos[i]))
			error_msg(p, 4);
		i++;
	}
	i = 0;
	pthread_join(monitor_thread, NULL);
	while (i < p->num_philos)
	{
		pthread_join(p->thread[i], NULL);
		i++;
	}
}

void	only_one_philosopher(t_data *p)
{
	msg_lock(&p->philos[0], 0);
	ft_usleep(p->time_to_die);
	msg_lock(&p->philos[0], 4);
	free_philos(p);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	*p;

	current_time(0);
	p = malloc(sizeof(t_data));
	if (!p)
		error_msg(p, 0);
	if (argc != 5 && argc != 6)
		error_msg(p, 1);
	if (arg_check(argv))
		error_msg(p, 2);
	init_argv(argc, argv, p);
	init_forks(p);
	init_philos(p);
	distribute_forks(p);
	if (p->num_philos == 1)
		only_one_philosopher(p);
	start_simulation(p);
	free_philos(p);
}
