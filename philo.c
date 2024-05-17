/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:40:07 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/17 03:22:10 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

int main(int ac, char **av)
{
	t_data data;
	if ((ac == 5 || ac == 6))
	{
		if (check_input(ac, av) && data_init(ac, av, &data))
		{
			printf("init\n");
			start_simulation(&data);
			printf("simulation ended\n");
			clear_all(&data);
			printf("cleared\n");
		}
	}
	else
	{
		printf("\033[1;31m Args Error ❌\033[0m\n");
		printf("\033[1;36m Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\033[0m\n");
	}
	return 0;
}