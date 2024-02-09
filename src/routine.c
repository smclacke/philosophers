/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:29:12 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/09 17:17:51 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	check_stop_b(t_philo *philo)
{
	bool		stop_check;

	pthread_mutex_lock(&philo->data->prog_m[STOP]);
	stop_check = philo->data->stop_b;
	pthread_mutex_unlock(&philo->data->prog_m[STOP]);
	return (stop_check);
}

/**
 * stop every philo trying to eat at very start
 * half start eating while half think for the eat time
*/
static void	waiting(t_philo *philo)
{
	display_message(philo, THINKING);
	ft_sleep(philo, philo->data->time_eat);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork_m);
	display_message(philo, TAKEN_FORK);
	if (philo->data->philo_count == 1)
	{
		ft_sleep(philo, philo->data->time_eat);
		return(1);
	}
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
	return (0);
}

/**
 * to stop a deadlock, if a philo has some time to spare, 
 * it sleeps for a bit to give a more hungry philo the chance
 * to get forks first
*/
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

/**
 * starting with the start mutex, all philos are
 * queuing here until start mutex is unlocked in 
 * create_threads() after all threads are made
 * and start bool is set, ensuring no philo gets
 * a head start
 *
 * all odd numbered philos start by waiting eat_time 
 * all even numbered philos can start eating
 * 
 * if philo has lots of time since last eaten and before
 * death, it can wait to give eating priority to
 * other more hungry philos
 * 
 * if not eating, must sleep sleep arg amount
 * otherwise they are doing something thinking
*/
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
		if (eat(philo) == 1)
			return (NULL);
		display_message(philo, SLEEPING);
		ft_sleep(philo, philo->data->time_sleep);
		display_message(philo, THINKING);
	}
	return (NULL);
}
