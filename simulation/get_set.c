/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:30:29 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/13 06:44:30 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool get_bool(pthread_mutex_t *mutex, bool *value)
{
	bool result;
	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

void set_long(pthread_mutex_t *mutex, long *dest, long value)
{
	pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long get_long(pthread_mutex_t *mutex, long *value)
{
	long result;
	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}

bool running_simulation(t_data *data)
{
	return (get_bool(&data->table_mutex, &data->monitor));
}

void	long_incrementation(pthread_mutex_t *mutex, long *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}
