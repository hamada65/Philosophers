/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-rhay <mel-rhay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 02:56:07 by mel-rhay          #+#    #+#             */
/*   Updated: 2024/05/23 22:59:38 by mel-rhay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	int_valid2(char **nb, int *len)
{
	while (**nb == ' ')
		(*nb)++;
	if (**nb == '+')
		(*nb)++;
	else if (**nb == '-')
	{
		printf("\033[1;31m Only Positive Numbers ❌\033[0m\n");
		return (false);
	}
	if (!(**nb >= '0' && **nb <= '9'))
	{
		printf("\033[1;31m Not Valid Number ❌\033[0m\n");
		return (false);
	}
	while (**nb >= '0' && **nb <= '9')
	{
		(*len)++;
		(*nb)++;
	}
	return (true);
}

bool	int_valid(char *nb)
{
	int		len;
	long	number;

	len = 0;
	number = ft_atol(nb);
	if (!int_valid2(&nb, &len))
		return (false);
	while (*nb)
	{
		if (*nb != ' ')
		{
			printf("\033[1;31m Only Numbers ❌\033[0m\n");
			return (false);
		}
		nb++;
	}
	if (len > 10 || number > INT_MAX)
	{
		printf("\033[1;31m More That INT_MAX ❌\033[0m\n");
		return (false);
	}
	return (true);
}

bool	check_input(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!int_valid(av[i]))
			return (false);
		i++;
	}
	return (true);
}
