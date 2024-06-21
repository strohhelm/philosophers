/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:55:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 17:05:30 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_for_creation(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (data->group[i].time_of_death. != -1)
			i++;
		else
			usleep(10);
	}
	return ;
}

int	*allocate_value_array(int nb_of_philos)
{
	int	i;
	int	*arr;

	arr = (int *)malloc(sizeof(int) * nb_of_philos);
	if (!arr)
		return (NULL);
	i = -1;
	while (++i < nb_of_philos)
		arr[i] = i;
	return (arr);
}
