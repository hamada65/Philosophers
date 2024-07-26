/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 04:11:15 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/07/26 22:35:40 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	gettime(t_time type)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	if (type == SECOND)
		return (now.tv_sec);
	else if (type == MILLISECOND)
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	else if (type == MICROSECOND)
		return (now.tv_sec * 1000000 + now.tv_usec);
	return (0);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(30, philo->data);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, false);
	}
}

void	my_usleep(long time, t_data *data)
{
	long	now;

	now = gettime(MILLISECOND);
	while (gettime(MILLISECOND) - now < time)
	{
		if (!running_simulation(data))
			break;
		usleep(50);
	}
}
