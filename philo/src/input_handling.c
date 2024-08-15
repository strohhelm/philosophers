/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:40:11 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/15 13:57:55 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	validate_argv(int argc, char **argv)
{
	int		i;
	char	*s;

	i = 1;
	while (i < argc)
	{
		s = argv[i];

		if (!*s)
			return (ERROR);
		while (*s)
		{
			if (*s < 48 || *s > 57)
				return (ERROR);
			s++;
		}
		i++;
	}
	return (SUCCESS);
}

int	initialize_input(int argc, char **argv, t_input *data)
{
	int err;

	err = SUCCESS;
	if (validate_argv(argc, argv) != SUCCESS)
		return (ERROR);
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	if (data->nb_of_philos == 0)
		return (ERROR);
	return (SUCCESS);
}
