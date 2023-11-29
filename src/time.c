/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:40:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/29 10:54:01 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * each philo has their own last_eaten_t time
 * calculated from the moment they begin eating
*/
void	last_eaten_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner_time_m);
	philo->last_eaten_t = current_time(philo->data->start_time_t);
	pthread_mutex_unlock(&philo->dinner_time_m);
}

/**
 * if you were to use usleep(10), trying to sleep an accurate 
 * amount of time can cause usleep() to be a lot less accurate
 * e.g. usleep(10) will have loads of calls to the system and 
 * the CPU will be over loaded causing small but many discrepancies, 
 * each time a slight delay is created 
 * usleep(250) sleeps incremently while not calling the system so much
 * 
 * ensure after a philo has died, that we don't continue
 * to sleep but the simulation just prints and stops
*/
void	ft_sleep(t_philo *philo, int waiting)
{
	uint64_t	start;

	start = ft_get_time();
	if (check_stop_b(philo) == true)
		return ;
	usleep((waiting / 2) * 1000);
	while ((ft_get_time() - start) < (uint64_t) waiting)
	{
		if (check_stop_b(philo) == true)
			break ;
		usleep(250);
	}
}

/**
 * @brief	time function in milliseconds from start of philo life
 */
uint64_t	current_time(uint64_t start)
{
	return ((unsigned long int)ft_get_time() - start);
}

/**
 * @brief	using gettimeofday function (microseconds from jan 1970)
 * 			 get time in milliseconds
 */
uint64_t	ft_get_time(void)
{
	struct timeval			time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
