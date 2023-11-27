/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 17:40:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/27 19:44:46 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	last_eaten_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->dinner_time_m);
	philo->last_eaten_t = current_time(philo->data->start_time_t);
	pthread_mutex_unlock(&philo->dinner_time_m);
}

/**
 * if you were to use usleep(10), trying to get it that acurate 
 * will cause it to be a lot less acurate since usleep(10) will have
 * loads of calls to the system (server? / CPU), each time creating
 * a slight delay/a few seconds less acurate 
 * usleep(250) sleeps incremently while not calling the system so much
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
 * 
 * @param	data pass the start time of philo life and then start the clock
 * @return	unsigned long int milliseconds since philo life started
 */
uint64_t	current_time(uint64_t start)
{
	return ((unsigned long int)ft_get_time() - start);
}

/**
 * @brief	using gettimeofday function (microseconds from jan 1970)
 * 			 get time in milliseconds
 * 
 * @return	long current milliseconds since 1970
 */
uint64_t	ft_get_time(void)
{
	struct timeval			time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
