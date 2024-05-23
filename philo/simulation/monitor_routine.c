/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 05:37:02 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/18 05:11:29 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	check_dead(t_philo *philo)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->max))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal);
	t_to_die = philo->data->time_to_die;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}

bool	all_started(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philo;
	while (tmp)
	{
		if (tmp->last_meal == -1)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

bool	all_reached_max(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philo;
	while (tmp)
	{
		if (!get_bool(&tmp->philo_mutex, &tmp->max))
			return (false);
		tmp = tmp->next;
	}
	return (true);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;
	t_philo	*tmp;

	data = (void *)arg;
	while (!all_started(data))
		;
	while (running_simulation(data))
	{
		tmp = data->philo;
		while (tmp && running_simulation(data))
		{
			if (check_dead(tmp))
			{
				set_bool(&data->table_mutex, &data->monitor, false);
				printf("\033[1;37m⏰\033[0m [%ld]\t🧐 Philo [%d] %s\033[0m\n",
					gettime(MILLISECOND) - data->start_time, tmp->id,
					"\033[1;31mis dead 💀");
			}
			if (data->required_meals != -1 && all_reached_max(data))
				set_bool(&data->table_mutex, &data->monitor, false);
			tmp = tmp->next;
		}
	}
	return (NULL);
}
