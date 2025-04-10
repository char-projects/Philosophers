/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 01:03:48 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/10 20:34:27 by cschnath         ###   ########.fr       */
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
	else if (code == 5)
		str = "is dead in main";
	else
		return ;
	pthread_mutex_lock(p->write_lock);
	printf("%zu %d %s\n", current_time(1), p->id, str);
	pthread_mutex_unlock(p->write_lock);
}

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = current_time(1);
	while ((current_time(1) - start) < ms)
		usleep(500);
}

size_t	current_time(int flag)
{
	struct timeval			time;
	static struct timeval	start;

	if (flag == 0)
	{
		gettimeofday(&start, NULL);
		return (0);
	}
	else
	{
		gettimeofday(&time, NULL);
		return ((time.tv_sec - start.tv_sec) * 1000 + (time.tv_usec
				- start.tv_usec) / 1000);
	}
}

void	ft_eat(t_philos *p)
{
	if (!ft_is_dead(p))
	{
		if (p->meals_eaten >= p->data->num_to_eat && p->data->num_to_eat != -1)
			return ;
		if (pthread_mutex_lock(p->l_fork) != 0)
			return ;
		if (!ft_is_dead(p))
			msg_lock(p, 0);
		if (pthread_mutex_lock(p->r_fork) != 0)
		{
			pthread_mutex_unlock(p->l_fork);
			return ;
		}
		if (!ft_is_dead(p))
			msg_lock(p, 0);
		if (!ft_is_dead(p))
			msg_lock(p, 1);
		pthread_mutex_lock(p->meal_lock);
		p->last_meal = current_time(1);
		p->meals_eaten++;
		pthread_mutex_unlock(p->meal_lock);
		ft_usleep(p->data->time_to_eat);
		pthread_mutex_unlock(p->l_fork);
		pthread_mutex_unlock(p->r_fork);
	}
}

int	arg_check(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
