/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocating_and_initiating.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:41:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 17:05:18 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	allocate_stuff(t_input *data)
{
	int	i;

	data->group = (t_philo *)malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->group)
		return (printf("ERROR allocating philos\n"), 1);
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * data->nb_of_philos);
	if (!data->forks)
		return (printf("ERROR allocating forks\n"), free(data->group), 1);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		if (pthread_mutex_init(&data->group[i].local_end.lock, NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		if (pthread_mutex_init(&data->group[i].time_of_death.lock, NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		if (pthread_mutex_init(&data->group[i].nb.lock, NULL))
			return (printf("ERROR create mutex %d\n", i), ft_free(data, i), 1);
		i++;
	}
	if (init_rest_mutexes(data, i))
		return (1);
	return (0);
}

int	init_rest_mutexes(t_input *data, int i)
{
	if (pthread_mutex_init(&data->print, NULL))
		return (ft_free(data, i), 1);
	if (pthread_mutex_init(&data->time, NULL))
		return (ft_free(data, i), 1);
	if (pthread_mutex_init(&data->end_flag.lock, NULL))
		return (ft_free(data, i), 1);
	return (0);
}

int	create_threads(t_input *data)
{
	int	i;
	int	j;
	int	*nb;

	i = 0;
	j = data->nb_of_philos;
	nb = allocate_value_array(data->nb_of_philos);
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->group[*nb].id, NULL, &philos,
				(void *)&data->group[*nb]))
			return (printf("ERROR create thread %d\n", i), ft_free(data, j), 1);
		i++;
		nb++;
	}
	if (pthread_create(&data->deathwatch, NULL, &death_watching, (void *)data))
		return (printf("ERROR creating deathwatch\n"), ft_free(data, j), 1);
	wait_for_creation(data);
	free(nb - i);
	return (0);
}

void	init_group(t_input *data)
{
	int	i;
	int	left_fork_index;
	int	right_fork_index;

	i = 0;
	while (i < data->nb_of_philos)
	{
		left_fork_index = i - 1;
		right_fork_index = i;
		if (i == 0)
			left_fork_index = data->nb_of_philos - 1;
		data->group[i].nb.value = i + 1;
		data->group[i].l_fork = &data->forks[left_fork_index];
		data->group[i].r_fork = &data->forks[right_fork_index];
		data->group[i].print = &data->print;
		data->group[i].time = &data->time;
		data->group[i].sleep_time = data->time_to_sleep;
		data->group[i].eat_time = data->time_to_eat;
		data->group[i].time_to_die = data->time_to_die;
		data->group[i].times_must_eat = data->times_must_eat;
		data->group[i].end_flag = &data->end_flag;
		data->group[i].time_of_death.value = -2;
		data->group[i].local_end.value = 0;
		i++;
	}
}
