/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 03:04:25 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/23 22:00:31 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_add_back(t_philo **alst, t_philo *new)
{
	t_philo	*tmp;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	assign_forks(t_data *data, t_philo *tmp, int i)
{
	tmp->left_fork = &data->forks[(i + 1) % data->nb_philo];
	tmp->right_fork = &data->forks[i];
	if (tmp->id % 2 == 0)
	{
		tmp->left_fork = &data->forks[i];
		tmp->right_fork = &data->forks[(i + 1) % data->nb_philo];
	}
}

bool	init_philo(t_data *data)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < data->nb_philo)
	{
		tmp = malloc(sizeof(t_philo));
		if (!tmp)
			return (false);
		tmp->id = i + 1;
		tmp->meals_nb = 0;
		tmp->last_meal = -1;
		assign_forks(data, tmp, i);
		philo_add_back(&data->philo, tmp);
		tmp->next = NULL;
		tmp->data = data;
		tmp->max = false;
		pthread_mutex_init(&tmp->philo_mutex, NULL);
		i++;
	}
	return (true);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->table_mutex, NULL);
}

bool	data_init(int ac, char **av, t_data *data)
{
	data->required_meals = -1;
	if (ac == 6)
		data->required_meals = ft_atol(av[5]);
	data->nb_philo = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->philo = NULL;
	data->monitor = true;
	data->ready_to_start = false;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
	{
		printf("\033[1;31m Memory Allocation Error ❌\033[0m\n");
		return (false);
	}
	if (!init_philo(data))
	{
		free(data->forks);
		clear_philos(data->philo);
		printf("\033[1;31m Memory Allocation Error ❌\033[0m\n");
		return (false);
	}
	init_mutex(data);
	return (true);
}
