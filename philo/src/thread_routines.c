/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_routines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:10:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/03 15:59:41 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philos(void *arg)
{
	t_philo	*philo;
	int		counter;
	int		i;

	philo = (t_philo *)arg;
	val_set(&philo->time_of_last_meal, get_time(philo->time));
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
		i = 0;
		while (i < data->nb_of_philos && flag_check(&data->end_flag) == DOWN)
		{
			time = get_time(&data->time);
			if (val_comp(&data->group[i].time_of_last_meal, -2) != BIGGER)
				;
			else if (local_end_check(data) == ERROR)
				break ;
			else if (val_get(&data->group[i].time_of_last_meal)
				<= time - data->time_to_die)
			{
				flag_set(&data->end_flag, 1);
				safe_printf("died", time, &data->group[i], UP);
			}
			i++;
		}
	}
	return (NULL);
}

int	local_end_check(t_input *data)
{
	int	i ;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_of_philos)
	{
		if (flag_check(&data->group[i].local_end) == UP)
			j++;
		i++;
	}
	if (j == i)
	{
		flag_set(&data->end_flag, 1);
		return (ERROR);
	}
	return (SUCCESS);
}
