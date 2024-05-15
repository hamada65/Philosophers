/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 04:11:15 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/15 03:19:55 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	gettime(t_time type)
{
	struct timeval now;

	gettimeofday(&now, NULL);
	//gettime in seconds
	if (type == SECOND)
		return (now.tv_sec);
	else if (type == MILLISECOND)
		return (now.tv_sec * 1000 + now.tv_usec / 1000);
	else if (type == MICROSECOND)
		return (now.tv_sec * 1000000 + now.tv_usec);
	else
		error_handling("gettime error");
	return (0);
}

void error_handling(char *error)
{
	printf("Error : %s\n", error);
	exit(1337);
}

void	de_synchronize_philos(t_philo *philo)
{
	if (philo->data->nb_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			my_usleep(30);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}

void my_usleep(long time)
{
	long	now;

	now = gettime(MILLISECOND);
	while (gettime(MILLISECOND) - now < time)
		usleep(50);
}