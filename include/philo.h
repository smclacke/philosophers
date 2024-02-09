/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 16:21:33 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/09 17:21:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <time.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <inttypes.h>

// ----- init input -----//
int				init_input(t_god *info, int argc, char **argv);

// -----init_philos -----//
int				create_philo_struct(t_god *info);

// ----- mutexes -----//
int				assign_forks(t_god *info);
int				create_eat_amount_mutex(t_god *info);
int				create_dinner_time_mutex(t_god *info);
int				create_forks_mutex(t_god *info);
int				create_prog_mutex(t_god *info);

// ----- life_cycle -----//
int				life_cycle(t_god *info);

// ----- routine -----//
bool			check_stop_b(t_philo *philo);
void			*routine(void *data);

// ----- monitor -----//
void			monitor(t_god *info);

// ----- ft_atoi -----//
int				ft_atoi(char *str);

// ----- time -----//
void			last_eaten_time(t_philo *philo);
void			ft_sleep(t_philo *philo, int waiting);
uint64_t		current_time(uint64_t start);
uint64_t		ft_get_time(void);

// ----- destroy_mutexes -----//
void			destroy_eat_amount_mutex(t_god *info, int amount);
void			destroy_dinner_time_mutex(t_god *info, int amount);
void			destroy_mutexes(pthread_mutex_t *mutex, int amount);
void			destroy_everything(t_god *info);

// ----- error -----//
void			ft_error_args(int argc);
int				ft_error(char *str);

// ----- utils -----//
void			free_info(t_god *info);
void			display_message(t_philo *philo, char *msg);

#endif
