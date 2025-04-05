/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/05 18:33:43 by cschnath         ###   ########.fr       */
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

void	only_one_philosopher(t_data *p)
{
	ft_printf("%d %d has taken a fork\n", 0, p->philos[0].id);
	// I think I have to make my own usleep function
    usleep(p->time_to_die * 1000);
	ft_printf("%d %d died\n", p->time_to_die, p->philos[0].id);
	free_philos(p);
	exit(0);
}

// Arguments in milliseconds
int	main(int argc, char **argv)
{
	t_data	*p;

	// Allocate memory for philosophers
	p = malloc(sizeof(t_philos) * (ft_atoi(argv[1])));
	if (!p)
		error_msg(p, 0);
	// Check the number of arguments
	if (argc != 5 && argc != 6)
		error_msg(p, 1);
	// Initialize everything
	init_argv(argc, argv, p);
	init_philos(p);
	init_forks(p);
	// Handle the case of only one philosopher
	if (p->num_philos == 1)
		only_one_philosopher(p);
	// Start the simulation
	ft_printf("Starting simulation with %d philosophers...\n", p->num_philos);
	// Clean up and exit
	free_philos(p);
}
