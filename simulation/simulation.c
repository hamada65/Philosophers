/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:23:14 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/15 03:07:36 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void print_status(long start, char *status, t_philo *philo, long now)
{
	long time;

	if (philo->max || !running_simulation(philo->data))
		return ;
	time = now - start;
	printf("%ld Philo %d %s\n", time, philo->id, status);
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
	printf("finished all threads");
	pthread_join(data->monitor_thread, NULL);
	// mean all philo are full
}