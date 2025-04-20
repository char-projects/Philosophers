/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschnath <cschnath@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 13:33:44 by cschnath          #+#    #+#             */
/*   Updated: 2025/04/20 18:04:48 by cschnath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_data
{
	int				num_philos;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_to_eat;
	pthread_t		*thread;
	pthread_mutex_t	*forks;
	struct s_philos	*philos;
}					t_data;

typedef struct s_philos
{
	int				id;
	int				meals_eaten;
	size_t			last_meal;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*write_lock;
	int				dead;
	t_data			*data;
}					t_philos;

// cleanup.c
int					error_msg(t_data *p, int error_code);
void				msg_lock(t_philos *p, int code);
void				free_philos(t_data *p);

// init.c
int					init_argv(int argc, char **argv, t_data *p);
int					init_forks(t_data *p);
int					init_philos(t_data *p);
void				distribute_forks(t_data *p);

// main.c
void				*ft_state(void *tmp_p);
int					start_simulation(t_data *p);
void				only_one_philosopher(t_data *p);

// monitor.c
int					check_death(t_philos *p, t_data *data);
int					ft_is_dead(t_philos *p);
void				kill_all(t_data *p);
int					check_meals(t_data *p);
void				*monitor(void *tmp_p);

// utils.c
void				ft_usleep(size_t ms);
size_t				current_time(int flag);
void				ft_eat(t_philos *p);
int					arg_check(char **argv);
int					ft_atoi(const char *str);

#endif
