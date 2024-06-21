/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 12:22:14 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philos(void *arg)
{
	t_philo	*philo;
	int		counter;

	philo = (t_philo *)arg;
	philo->time_of_death = get_time(philo->time) + philo->time_to_die;
	counter = 0;
	if (philo->nb % 2 == 0)
		usleep(philo->eat_time / 2);
	while (*(philo->end_flag) == 0 && philo->local_end == 0
		&& philo->times_must_eat > 0)
	{
		think(philo, &philo->local_end);
		if (philo->local_end != 0)
			return (NULL);
		if (*(philo->end_flag))
			return (unlock_both(philo), NULL);
		eat(philo);
		if (*(philo->end_flag) == 0 && ft_sleep(philo))
			counter++;
	}
	philo->local_end = 1;
	return (NULL);
}

void	*death_watching(void *arg)
{
	t_input		*data;
	int			i;
	long		time;

	data = (t_input *)arg;
	while (data->end_flag == 0)
	{
		i = 0;
		while (i < data->nb_of_philos && data->end_flag == 0)
		{
			time = get_time(&data->time);
			if (data->group[i].time_of_death > -2)
			{
				local_end_check(data);
				if (data->group[i].time_of_death <= time)
				{
					data->end_flag = 1;
					safe_printf("died", time, data->group[i].nb, &data->print);
				}
			}
			i++;
		}
	}
	return (NULL);
}
