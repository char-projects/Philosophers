/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:44 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/05 20:20:39 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/include/libft.h"
# include <pthread.h>

typedef struct s_philos
{
	int				id; // Initialized
	int				meals_eaten; // Initialized
	int				last_meal; // Initialized

	int				*l_fork;
	int				*r_fork;

	int				died; // Initialized
}					t_philos;

typedef struct s_data
{
	int				dead; // Initialized

	int				num_philos; // Initialized
	int				time_to_die; // Initialized
	int				time_to_eat; // Initialized
	int				time_to_sleep; // Initialized
	int				num_to_eat; // Initialized

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
void				*ft_state(void *tmp_p);
void				start_simulation(t_data *p);
void				only_one_philosopher(t_data *p);

#endif
