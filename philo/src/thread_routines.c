/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/05 16:32:17 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philos(void *arg)
{
	t_philo	*philo;
	int		counter;
	int		i;

	philo = (t_philo *)arg;
	val_set(&philo->time_of_last_meal, 0);
	counter = 0;
	while (flag_check(philo->end_flag) == DOWN)
	{
		if (counter == 0)
			i = 1;
		else
			i = 0;
		if (thinking(philo, i) == ERROR)
			return (NULL);
		if (eating(philo) == ERROR)
			return (NULL);
		if (sleeping(philo) == ERROR)
			return (NULL);
		counter = 1;
	}
	return (NULL);
}

void	*death_watching(void *arg)
{
	t_input		*data;
	int			i;
	long		time;

	data = (t_input *)arg;
	while (flag_check(&data->end_flag) == DOWN && data->nb_of_philos > 0)
	{
		i = -1;
		while (++i < data->nb_of_philos && flag_check(&data->end_flag) == DOWN)
		{
			time = get_time();
			if (val_get(&data->finished) >= data->nb_of_philos)
				flag_set(&data->end_flag, UP);
			else if (val_get(&data->group[i].time_of_last_meal)
				<= time - data->time_to_die)
			{
				pthread_mutex_lock(&data->print);
				flag_set(&data->end_flag, UP);
				printf("%ld %d died\n", get_time() / 1000, i + 1);
				pthread_mutex_unlock(&data->print);
			}
		}
		usleep(200);
	}
	return (NULL);
}
