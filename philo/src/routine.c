/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:29:12 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 20:11:50 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * for routine while loop, if not locked, get data race when setting
 * stop_b in display_message() || eaten_enough()
*/
bool	check_stop_b(t_philo *philo)
{
	bool		stop_check;

	pthread_mutex_lock(&philo->data->prog_m[STOP]);
	stop_check = philo->data->stop_b;
	pthread_mutex_unlock(&philo->data->prog_m[STOP]);
	return (stop_check);
}

/**
 * stop every philo going for a fork at one time
 * half start eating while half think for the eat time
*/
static void	waiting(t_philo *philo)
{
	display_message(philo, THINKING);
	ft_sleep(philo, philo->data->time_eat);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork_m);
	display_message(philo, TAKEN_FORK);
	pthread_mutex_lock(philo->rfork_m);
	display_message(philo, TAKEN_FORK);
	last_eaten_time(philo);
	display_message(philo, EATING);
	ft_sleep(philo, philo->data->time_eat);
	if (philo->data->eat_arg_b == true)
	{
		pthread_mutex_lock(&philo->eat_xamount_m);
		philo->x_eaten++;
		pthread_mutex_unlock(&philo->eat_xamount_m);
	}
	pthread_mutex_unlock(philo->lfork_m);
	pthread_mutex_unlock(philo->rfork_m);
}

static void	check_time_gap(t_philo *philo)
{
	uint64_t	time_gap;
	uint64_t	enough_time;
	uint64_t	time_die;
	uint64_t	time_eat;

	pthread_mutex_lock(&philo->dinner_time_m);
	time_gap = current_time(philo->data->start_time_t) - philo->last_eaten_t;
	time_die = (uint64_t)philo->data->time_die;
	time_eat = (uint64_t)philo->data->time_eat;
	enough_time = (time_die - time_eat);
	if (time_gap < enough_time)
		ft_sleep(philo, philo->data->time_eat);
	pthread_mutex_unlock(&philo->dinner_time_m);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->data->prog_m[START]);
	pthread_mutex_unlock(&philo->data->prog_m[START]);
	if (philo->data->yes_start_b == false)
		return (NULL);
	if (philo->id % 2 != 0)
		waiting(philo);
	while (check_stop_b(philo) == false)
	{
		check_time_gap(philo);
		eat(philo);
		display_message(philo, SLEEPING);
		ft_sleep(philo, philo->data->time_sleep);
		display_message(philo, THINKING);
	}
	return (NULL);
}
