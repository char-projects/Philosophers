/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:03:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 13:41:50 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	msg_lock(t_philos *p, int code)
{
	char	*str;
	
	if (code == 0)
		str = "has taken a fork";
	else if (code == 1)
		str = "is eating";
	else if (code == 2)
		str = "is sleeping";
	else if (code == 3)
		str = "is thinking";
	else if (code == 4)
		str = "died";
	else
		return ;
	pthread_mutex_lock(p->write_lock);
	printf("%zu %d %s\n", current_time(), p->id, str);
	pthread_mutex_unlock(p->write_lock);
}

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
