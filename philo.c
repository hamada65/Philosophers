/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 02:40:07 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/11 03:22:42 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philo.h"

int main(int ac, char **av)
{
	t_data data;
	if ((ac == 5 || ac == 6) && data_init(ac, av, &data))
	{
		start_simulation(&data);
	}
	else
		printf("Error\n");
	return 0;
}