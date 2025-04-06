/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:44 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/06 13:40:28 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "../libft/include/libft.h"
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				dead; // Initialized

	int				num_philos; // Initialized
	int				time_to_die; // Initialized
	int				time_to_eat; // Initialized
	int				time_to_sleep; // Initialized
	int				num_to_eat; // Initialized

	pthread_mutex_t *forks; // Initialized
	struct s_philos	*philos;
}					t_data;

typedef struct s_philos
{
	int				id; // Initialized
	int				meals_eaten; // Initialized
	int				last_meal; // Initialized

	pthread_mutex_t	*l_fork; // Initialized
	pthread_mutex_t	*r_fork; // Initialized

	int				died; // Initialized

	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;

	t_data			*data;
}					t_philos;

// cleanup.c
void				error_msg(t_data *p, int error_code);
void				free_philos(t_data *p);

// init.c
void				init_argv(int argc, char **argv, t_data *p);
void				init_philos(t_data *p);
void				init_forks(t_data *p);

// logs.c
void				ft_eat(t_philos *p);
void				ft_sleep(t_philos *p);
void				ft_think(t_philos *p);
void				ft_die(t_philos *p);

// main.c
void				*ft_state(void *tmp_p);
void				start_simulation(t_data *p);
void				only_one_philosopher(t_data *p);

// utils.c
void				msg_lock(t_philos *p, int code);
void				ft_usleep(int ms);
size_t				current_time(void);

#endif
