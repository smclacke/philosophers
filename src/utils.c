/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/16 17:46:43 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/21 22:09:14 by SarahLouise   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	free_info(t_god *info)
{
	free(info->data->forks_m);
	free(info->data->prog_m);
	free(info->data);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

/**
 * if the message that needs to be printed is "died"
 * immediately after, set the stop_b to true
 * before printing anything other than "died"
 * check that stop_b, if we need to stop, we will not print
*/
void	display_message(t_philo *philo, char *msg)
{
	uint64_t	time;

	pthread_mutex_lock(&philo->data->prog_m[DISPLAY]);
	time = current_time(philo->data->start_time_t);
	if (ft_strcmp(msg, DIED) == 0)
	{
		printf("%llu %d %s\n", time, philo->id, msg);
		pthread_mutex_lock(&philo->data->prog_m[STOP]);
		philo->data->stop_b = true;
		pthread_mutex_unlock(&philo->data->prog_m[STOP]);
	}
	if (check_stop_b(philo) == true)
		pthread_mutex_unlock(&philo->data->prog_m[DISPLAY]);
	else
	{
		printf("%llu %d %s\n", time, philo->id, msg);
		pthread_mutex_unlock(&philo->data->prog_m[DISPLAY]);
	}
}
