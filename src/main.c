/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/08 01:26:39 by cschnath         ###   ########.fr       */
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

void	*ft_state(void *tmp_p)
{
	int			i;
	t_philos	*p;

	p = (t_philos *)tmp_p;
	i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(p->dead_lock);
        if (p->data->dead)
        {
            pthread_mutex_unlock(p->dead_lock);
            break;
        }
        pthread_mutex_unlock(p->dead_lock);
		ft_eat(p);
		ft_sleep(p);
		ft_think(p);
		i++;
	}
	return (NULL);
}

void	start_simulation(t_data *p)
{
	int			i;
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * (p->num_philos + 1));
	if (!thread)
		error_msg(p, 0);
	i = 0;
	while (i < p->num_philos)
	{
		pthread_create(&thread[i], NULL, ft_state, (void *)&p->philos[i]);
		i++;
	}
	pthread_create(&thread[i], NULL, monitor, (void *)p);
	i = 0;
	while (i <= p->num_philos)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(thread);
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
	t_data		*p;

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
