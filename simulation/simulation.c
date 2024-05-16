/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:23:14 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/16 01:16:57 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void print_status(long start, char *status, t_philo *philo, long now)
{
	long time;

	if (philo->max || !running_simulation(philo->data))
		return ;
	time = now - start;
	printf("\033[1;37m⏰\033[0m [%ld]\t🧐 Philo [%d] %s\033[0m\n", time, philo->id, status);
}

void	start_simulation(t_data *data)
{
	t_philo *tmp;

	if (!data->required_meals)
		return ;
	tmp = data->philo;
	while (tmp)
	{
		pthread_create(&tmp->thread, NULL, &philo_routine, tmp);
		tmp = tmp->next;
	}
	//monitoring thread
	pthread_create(&data->monitor_thread, NULL, &monitor_routine, data);
	// pthread_detach(data->monitor_thread);
	//set start simulation time
	data->start_time = gettime(MILLISECOND);
	
	//SET ALL THREAD AS READY
	set_bool(&data->table_mutex, &data->ready_to_start, true);

	//join all philo
	tmp = data->philo;
	while (tmp)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
	set_bool(&data->table_mutex, &data->monitor, false);	
	pthread_join(data->monitor_thread, NULL);
	// mean all philo are full
}