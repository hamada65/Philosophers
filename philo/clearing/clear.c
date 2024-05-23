/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 00:48:09 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/16 01:04:35 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clear_philos(t_philo *philo)
{
	t_philo	*tmp;

	while (philo)
	{
		pthread_mutex_destroy(&philo->philo_mutex);
		tmp = philo->next;
		free(philo);
		philo = tmp;
	}
}

void	clear_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->table_mutex);
	free(data->forks);
	clear_philos(data->philo);
}
