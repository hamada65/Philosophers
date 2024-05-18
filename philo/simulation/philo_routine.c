/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 03:47:22 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/18 05:11:25 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void wait_philosophers(t_data *data)
{
	while (!get_bool(&data->table_mutex, &data->ready_to_start));
}

void sleeping(t_philo *philo)
{
	print_status(philo->data->start_time, "\033[1;36mis sleeping 🛌", philo, gettime(MILLISECOND));
	my_usleep(philo->data->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo->data->start_time, "\033[1;33mhas taken left fork 🍴", philo, gettime(MILLISECOND));
	pthread_mutex_lock(philo->right_fork);
	print_status(philo->data->start_time, "\033[1;33mhas taken right fork 🍴", philo, gettime(MILLISECOND));
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	print_status(philo->data->start_time, "\033[1;32mis eating 🍽️", philo, gettime(MILLISECOND));
	philo->meals_nb++;
	my_usleep(philo->data->time_to_eat);
	if (philo->data->required_meals >= 0 && philo->meals_nb >= philo->data->required_meals)
		set_bool(&philo->philo_mutex, &philo->max, true);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void thinking(t_philo *philo, bool  pre_simul)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simul)
		print_status(philo->data->start_time, "\033[1;35mis thinking 💭", philo, gettime(MILLISECOND));
	if (philo->data->nb_philo % 2 == 0)
		return ;
	t_eat = philo->data->time_to_eat;
	t_sleep = philo->data->time_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	my_usleep(t_think * 0.42);
}

void *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	wait_philosophers(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal, gettime(MILLISECOND));
	de_synchronize_philos(philo);
	while (running_simulation(philo->data))
	{
		if (philo->max)
			break;
		eating(philo);
		sleeping(philo);
		thinking(philo, false);
	}
	return (NULL);
}
