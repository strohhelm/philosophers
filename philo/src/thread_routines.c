/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/24 17:19:00 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philos(void *arg)
{
	t_philo	*philo;
	int		counter;
	int		i;

	philo = (t_philo *)arg;
	val_set(&philo->time_of_death, get_time(philo->time) + philo->time_to_die);
	counter = 0;
	while (!flag_check(philo->end_flag) && !flag_check(&philo->local_end)
		&& philo->times_must_eat != 0)
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
		counter++;
	}
	flag_set(&philo->local_end, 1);
	return (NULL);
}

void	*death_watching(void *arg)
{
	t_input		*data;
	int			i;
	long		time;

	data = (t_input *)arg;
	while (flag_check(&data->end_flag) == DOWN)
	{
		i = 0;
		while (i < data->nb_of_philos && flag_check(&data->end_flag) == DOWN)
		{
			time = get_time(&data->time);
			if (val_comp(&data->group[i].time_of_death, -2) == BIGGER)
			{
				if (local_end_check(data) == ERROR)
					break ;
				if (val_comp(&data->group[i].time_of_death, time) != BIGGER)
				{
					flag_set(&data->end_flag, 1);
					safe_printf("died", time, data->group[i].nb, &data->print);
				}
			}
			i++;
		}
	}
	return (NULL);
}
