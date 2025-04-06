/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:03:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 04:03:13 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	ft_usleep(int ms)
{
	size_t	start;
	size_t  time;

	time = (size_t)ms;
	start = current_time();
	while ((current_time() - start) < time)
		usleep(500);
}

size_t	current_time(void)
{
	struct timeval			time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
