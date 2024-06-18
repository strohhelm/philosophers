/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:40:11 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/18 17:44:57 by pstrohal         ###   ########.fr       */
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
		while (*s)
		{
			if (*s < 48 || *s > 57)
				return (0);
			s++;
		}
		i++;
	}
	return (1);
}

int	initialize_input(int argc, char **argv, t_input *data)
{
	if (!validate_argv(argc, argv))
		return (1);
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]) * 1000;
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
		data->times_must_eat = ft_atoi(argv[5]);
	else
		data->times_must_eat = -1;
	data->end_flag = 0;
	return (0);
}

void	ft_free(t_input *data, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		pthread_mutex_destroy(&data->forks[i++]);
	}
	free(data->group);
	free(data->forks);
	return ;
}
