/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 10:08:16 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/24 14:36:46 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_free(t_input *data, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		if (data->fork_init[i] != 0)
			pthread_mutex_destroy(&data->forks[i]);
		if (data->group[i].local_end.init_flag != 0)
			pthread_mutex_destroy(&data->group[i].local_end.lock);
		if (data->group[i].time_of_death.init_flag != 0)
			pthread_mutex_destroy(&data->group[i].time_of_death.lock);
		i++;
	}
	p_dest(data, 3);
	free(data->group);
	free(data->forks);
	return ;
}

void	p_dest(t_input *data, int i)
{
	if (i-- > 0)
		pthread_mutex_destroy(&data->print);
	if (i-- > 0)
		pthread_mutex_destroy(&data->time);
	if (i-- > 0)
		pthread_mutex_destroy(&data->end_flag.lock);
	return ;
}

int	wait_for_philos(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(data->group[i].id, NULL) < 0)
		{
			safe_printf("pthread_join failed",
				get_time(&data->time), i, &data->print);
			return (ERROR);
		}
		i++;
	}
	if (pthread_join(data->deathwatch, NULL) < 0)
		return (printf("deathwatch_join failed %d\n", i), ERROR);
	return (SUCCESS);
}