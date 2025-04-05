/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:44 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/05 18:43:45 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/include/libft.h"
# include <pthread.h>

typedef struct s_philos
{
	int				id;
	int				meals_eaten;
	int				last_meal;

	int				*l_fork;
	int				*r_fork;

	int				died;
}					t_philos;

typedef struct s_data
{
	int				dead;

	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;

	pthread_mutex_t	*forks;
	t_philos		*philos;
}					t_data;

// cleanup.c
void				error_msg(t_data *p, int error_code);
void				free_philos(t_data *p);

// init.c
void				init_argv(int argc, char **argv, t_data *p);
void				init_philos(t_data *p);
void				init_forks(t_data *p);

// logs.c
void				ft_take_fork(t_philos *p);
void				ft_eat(t_philos *p);
void				ft_sleep(t_philos *p);
void				ft_think(t_philos *p);
void				ft_die(t_philos *p);

// main.c
void				only_one_philosopher(t_data *p);

#endif
