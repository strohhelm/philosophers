/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:45:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/18 17:45:46 by pstrohal         ###   ########.fr       */
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

void	safe_printf(char *s, long time, int nb, t_mutex *p_lock)
{
	pthread_mutex_lock(p_lock);
	printf("%ld %d %s\n", time / 1000, nb, s);
	pthread_mutex_unlock(p_lock);
	return ;
}

long	get_time(void)
{
	struct timeval	t;
	static long		start_time = 0;
	long			current_time;

	gettimeofday(&t, NULL);
	if (start_time == 0)
		start_time = t.tv_sec * 1000000 + (long)t.tv_usec;
	current_time = t.tv_sec * 1000000 + (long)t.tv_usec;
	return (current_time - start_time);
}

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
		i++;
	}
	if (pthread_mutex_init(&data->p_lock, NULL))
		return (ft_free(data, i), 1);
	return (0);
}

void	unlock_both(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}