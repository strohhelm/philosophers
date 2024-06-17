/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:16:04 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/17 19:21:38 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*philos(void *arg)
{
	t_philo	*philo;
	int		local_end;



	philo = (t_philo *)arg;
	local_end = 0;
	philo->time_of_death = get_time() + philo->time_to_die;
	while (*(philo->end_flag) == 0 && local_end == 0)
	{
		printf("%ld %d is thinking\n", get_time(), philo->nb);
		think(&philo->u, philo->nb, philo->end_flag);
		if (*(philo->end_flag) == 1)
			return (unlock_both(&philo->u), NULL);
		eat(philo, &local_end);
		if (*(philo->end_flag) == 1)
			break ;
		printf("%ld %d is sleeping\n", get_time(), philo->nb);
		usleep(philo->sleep_time);
	}
	printf("%ld %d returns5\n", get_time(), philo->nb);
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
			time = get_time();
			if (data->group[i].time_of_death < time)
			{
				printf("%ld %d died\n", time, data->group[i].nb);
				data->end_flag = 1;
			}
			i++;
		}
	}
	return (NULL);
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
		data->group[i].nb = i + 1;
		data->group[i].u.l_fork = &data->forks[left_fork_index];
		data->group[i].u.r_fork = &data->forks[right_fork_index];
		data->group[i].u.l_spoon = left_fork_index;
		data->group[i].u.r_spoon = right_fork_index;
		data->group[i].sleep_time = data->time_to_sleep;
		data->group[i].eat_time = data->time_to_eat;
		data->group[i].time_to_die = data->time_to_die;
		data->group[i].times_must_eat = data->times_must_eat;
		data->group[i].end_flag = &data->end_flag;
		i++;
	}
}

int	create_threads(t_input *data)
{
	int	i;
	int	j;

	i = 0;
	j = data->nb_of_philos;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&data->group[i].id, NULL, &philos,
				(void *)&data->group[i]))
			return (printf("ERROR create thread %d\n", i), ft_free(data, j), 1);
		i++;
	}
	if (pthread_create(&data->deathwatch, NULL, &death_watching, (void *)data))
		return (printf("ERROR creating deathwatch\n"), ft_free(data, j), 1);
	if (pthread_detach(data->deathwatch))
		return (printf("ERROR deathwatch detatch\n"), ft_free(data, j), 1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_input			data;
	int				i;

	if (argc == 5 || argc == 6)
	{
		if (initialize_input(argc, argv, &data))
			return (printf("INPUT ERROR\n"), 1);
		if (allocate_stuff(&data))
			return (1);
		init_group(&data);
		if (create_threads(&data))
			return (1);
		i = 0;
		while (i < data.nb_of_philos)
		{
			if (pthread_join(data.group[i].id, NULL) < 0)
				return (printf("pthread_join failed %d\n", i), 1);
			i++;
		}
		data.end_flag = 1;
		ft_free(&data, data.nb_of_philos);
		return (0);
	}
	printf("Wrong amount of arguments!\n");
	return (0);
}
