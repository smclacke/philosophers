/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:27:30 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/04 14:04:49 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <inttypes.h>

# define TRUE 1
# define FALSE 0

# define SUCCESS 0
# define ERROR 1

# define DIED "died"
# define TAKEN_FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

# define WRONG_ARGS "input must be an integer larger than 0"

/**
 * an array of mutexes to control the simulation
*/
typedef enum e_prog{
	START,
	STOP,
	DISPLAY,
	ALL
}			t_prog;

/**
 * @brief	_t time _b bool _m mutex
*/

typedef struct s_god		t_god;

typedef struct s_data{
	int						philo_count;
	int						time_die;
	int						time_eat;
	int						time_sleep;

	bool					eat_arg_b;
	int						eat_arg_count;

	uint64_t				start_time_t;
	bool					stop_b;
	bool					died_b;
	bool					yes_start_b;

	pthread_mutex_t			*forks_m;
	pthread_mutex_t			*prog_m;
}							t_data;

typedef struct s_philo{
	int						id;
	t_data					*data;
	int						x_eaten;
	uint64_t				last_eaten_t;

	bool					one_philo_b;

	pthread_mutex_t			eat_xamount_m;
	pthread_mutex_t			dinner_time_m;
	pthread_mutex_t			*lfork_m;
	pthread_mutex_t			*rfork_m;
	t_god					*info;
}							t_philo;

typedef struct s_god{
	t_data					*data;
	t_philo					*philipas;
}							t_god;

#endif
