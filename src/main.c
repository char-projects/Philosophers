/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/09 02:38:04 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Any state change of a philosopher must be formatted as follows:
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
Replace timestamp_in_ms with the current timestamp in milliseconds
and X with the philosopher number.
*/

#include "../include/philosophers.h"

int	ft_is_dead(t_philos *p)
{
	int death;
	
	death = 0;
	pthread_mutex_lock(p->dead_lock);
	if (p->data->dead == 1)
		death = p->data->dead;
	pthread_mutex_unlock(p->dead_lock);
	return (death);
}

void	*ft_state(void *tmp_p)
{
	t_philos	*p;

	p = (t_philos *)tmp_p;
	while (!ft_is_dead(p))
	{
		if (!ft_is_dead(p))
			ft_eat(p);
		if (!ft_is_dead(p))
			ft_sleep(p);
		if (!ft_is_dead(p))
			msg_lock(p, 3);
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
		if (pthread_create(&p->thread[i], NULL, ft_state, (void *)&p->philos[i]))
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

// Arguments in milliseconds
int	main(int argc, char **argv)
{
	t_data	*p;

	current_time(0);
	p = malloc(sizeof(t_data));
	if (!p)
		error_msg(p, 0);
	if (argc != 5 && argc != 6)
		error_msg(p, 1);
	init_argv(argc, argv, p);
	init_forks(p);
	init_philos(p);
	if (p->num_philos == 1)
		only_one_philosopher(p);
	start_simulation(p);
	free_philos(p);
}
