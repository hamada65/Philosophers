/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:30:07 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/08/11 16:06:53 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(t_data *data)
{
	data->start_time = gettime(MILLISECOND);
	print_status(data->start_time, "\033[1;33mhas taken left fork 🍴",
		data->philo, gettime(MILLISECOND));
	my_usleep(data->time_to_die);
	pthread_mutex_lock(&data->print_mutex);
	printf("\033[1;37m⏰\033[0m [%ld]\t🧐 Philo [%d] %s\033[0m\n",
		gettime(MILLISECOND) - data->start_time, data->philo->id,
		"\033[1;31mis dead 💀");
	pthread_mutex_unlock(&data->print_mutex);
}
