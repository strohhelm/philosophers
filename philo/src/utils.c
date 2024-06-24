/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:45:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/24 16:06:53 by pstrohal         ###   ########.fr       */
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

int	safe_printf(char *s, long time, int nb, t_mutex *p_lock)
{
	if (pthread_mutex_lock(p_lock) != SUCCESS)
		return (ERROR);
	printf("%ld %d %s\n", time / 1000, nb, s);
	if (pthread_mutex_unlock(p_lock) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

long	get_time(t_mutex *t_lock)
{
	struct timeval	t;
	static long		start_time = 0;
	long			current_time;

	pthread_mutex_lock(t_lock);
	gettimeofday(&t, NULL);
	if (start_time == 0)
		start_time = t.tv_sec * 1000000 + (long)t.tv_usec;
	current_time = t.tv_sec * 1000000 + (long)t.tv_usec;
	pthread_mutex_unlock(t_lock);
	return (current_time - start_time);
}

void	unlock_both(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
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
