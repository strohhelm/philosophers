/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:45:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/17 15:31:53 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int	ms;

	if (!str)
		return (-1);
	ms = 0;
	while (*str)
	{
		ms += *str - 48;
		if (*(str + 1))
			ms *= 10;
		str++;
	}
	return (ms);
}

long	get_time(void)
{
	struct timeval	t;
	long			time;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000000 + (long)t.tv_usec;
	return (time);
}

int	allocate_stuff(t_input *data)
{
	int	i;

	data->group = (t_philo *)malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->group)
		return (printf("ERROR allocating forks\n"), 1);
	data->spoon = (int *)malloc(sizeof(int) * data->nb_of_philos);
	if (!data->spoon)
		return (printf("ERROR allocating spoons\n"), free(data->group), 1);
	i = 0;
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->nb_of_philos);
	if (!data->forks)
		return (printf("ERROR allocating mutex array\n"), free(data->group), 1);
	while (i < data->nb_of_philos)
	{
		data->spoon[i] = 0;
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		i++;
	}
	return (0);
}

