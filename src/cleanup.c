/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:04:02 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 02:56:08 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	error_msg(t_data *p, int error_code)
{
	if (error_code == 0)
		ft_printf("Error: Memory allocation failed\n");
	else if (error_code == 1)
		ft_printf("Error: Invalid number of arguments\n");
	else if (error_code == 2)
		ft_printf("Error: Invalid argument values\n");
	else if (error_code == 3)
		ft_printf("Error: Mutex initialization failed\n");
	else if (error_code == 4)
		ft_printf("Error: Thread creation failed\n");
	free_philos(p);
	exit(1);
}

void	free_philos(t_data *p)
{
	free(p->philos);
	free(p);
}
