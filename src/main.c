/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 04:21:43 by cschnath         ###   ########.fr       */
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
	if (p->id % 2 == 0)
		usleep(100);
	else
		usleep(50);
	while (i < 2)
	{
		ft_sleep(p);
		ft_think(p);
		ft_eat(p);
		if (p->died)
			break ;
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
		pthread_join(thread[i], NULL);
		i++;
	}
}

void	only_one_philosopher(t_data *p)
{
	ft_printf("%d %d has taken a fork\n", 0, p->philos[0].id);
	// I think I have to make my own usleep function
	ft_usleep(p->time_to_die);
	ft_printf("%d %d died\n", p->time_to_die, p->philos[0].id);
	free_philos(p);
	exit(0);
}

// Arguments in milliseconds
int	main(int argc, char **argv)
{
	t_data		*p;

	// Allocate memory for philosophers
	p = malloc(sizeof(t_philos) * (ft_atoi(argv[1])));
	if (!p)
		error_msg(p, 0);
	// Check the number of arguments
	if (argc != 5 && argc != 6)
		error_msg(p, 1);
	// Initialize everything
	init_argv(argc, argv, p);
	init_forks(p);
	init_philos(p);
	// Handle the case of only one philosopher
	if (p->num_philos == 1)
		only_one_philosopher(p);
	// Start the simulation
	start_simulation(p);
	// Clean up and exit
	free_philos(p);
}
