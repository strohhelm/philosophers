/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_and_initiating.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:41:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/05 15:39:11 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	allocate_stuff(t_input *data)
{
	get_time();
	if (data->times_must_eat == 0)
		return (ERROR);
	data->group = (t_philo *)malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->group)
		return (printf("ERROR allocating philos\n"), ERROR);
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->nb_of_philos);
	if (!data->forks)
		return (printf("ERROR allocating forks\n"), free(data->group), ERROR);
	data->fork_init = (int *)malloc(sizeof(int) * data->nb_of_philos);
	if (!data->fork_init)
		return (printf("ERROR\n"), free(data->group), free(data->forks), ERROR);
	zero_mutex_indicators(data);
	if (pthread_mutex_init(&data->print, NULL))
		return (free(data->group), free(data->forks), p_dest(data, 0), ERROR);
	if (pthread_mutex_init(&data->end_flag.lock, NULL))
		return (free(data->group), free(data->forks), p_dest(data, 1), ERROR);
	if (pthread_mutex_init(&data->finished.lock, NULL))
		return (free(data->group), free(data->forks), p_dest(data, 2), ERROR);
	if (init_rest_mutexes(data) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	init_rest_mutexes(t_input *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		data->fork_init[i] = 1;
		if (pthread_mutex_init(&data->group[i].time_of_last_meal.lock, NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		data->group[i].time_of_last_meal.init_flag = 1;
		i++;
	}
	return (SUCCESS);
}

int	create_threads(t_input *data)
{
	int	i;
	int	j;
	int	*nb;

	i = 0;
	j = data->nb_of_philos;
	get_time();
	nb = allocate_value_array(data->nb_of_philos);
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->group[*nb].id, NULL, &philos,
				(void *)&data->group[*nb]))
			return (safe_printf("ERROR create thread\n",
					&data->group[i], UP), i);
		i++;
		nb++;
	}
	wait_for_creation(data);
	if (pthread_create(&data->deathwatch, NULL, &death_watching, (void *)data))
		return (safe_printf("ERROR creating deathwatch", &data->group[0], ERR),
			ft_free(data, j), ERROR);
	data->deathwatch_init = 1;
	free(nb - i);
	return (SUCCESS);
}

int	init_group(t_input *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philos)
	{
		data->group[i].l_fork = &data->forks[i - 1];
		if (i == 0)
			data->group[i].l_fork = &data->forks[data->nb_of_philos - 1];
		data->group[i].nb = i + 1;
		data->group[i].r_fork = &data->forks[i];
		data->group[i].eat_time = data->time_to_eat;
		data->group[i].sleep_time = data->time_to_sleep;
		data->group[i].time_of_last_meal.value = -2;
		data->group[i].times_must_eat = data->times_must_eat;
		data->group[i].end_flag = &data->end_flag;
		data->group[i].print = &data->print;
		data->group[i].finished = &data->finished;
	}
	data->end_flag.value = 0;
	data->finished.value = 0;
	return (SUCCESS);
}
