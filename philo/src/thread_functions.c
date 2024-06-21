/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 12:26:41 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, t_philo *p)
{
	pthread_mutex_lock(fork);
	if (*(p->end_flag) == 0)
		safe_printf("has taken a fork", get_time(p->time), p->nb, p->print);
	return ;
}

void	think(t_philo *philo, int *local_end)
{
	safe_printf("is thinking", get_time(philo->time), philo->nb, philo->print);
	if (*(philo->end_flag) != 0)
		return ;
	lock(philo->l_fork, philo);
	if (*(philo->end_flag) != 0 || philo->l_fork == philo->r_fork)
	{
		pthread_mutex_unlock(philo->l_fork);
		*local_end = -1;
		return ;
	}
	lock(philo->r_fork, philo);
	if (*(philo->end_flag) != 0)
	{
		unlock_both(philo);
		return ;
	}
	return ;
}

void	eat(t_philo *philo)
{
	philo->times_must_eat--;
	philo->time_of_death += philo->time_to_die;
	safe_printf("is eating", get_time(philo->time), philo->nb, philo->print);
	usleep(philo->eat_time);
	unlock_both(philo);
}

int	ft_sleep(t_philo *philo)
{
	safe_printf("is sleeping", get_time(philo->time), philo->nb, philo->print);
	if (*(philo->end_flag) == 0)
	{
		usleep(philo->sleep_time);
		return (1);
	}
	return (0);
}

void	local_end_check(t_input *data)
{
	int	i ;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_of_philos)
	{
		if (data->group[i].local_end == 1)
			j++;
		i++;
	}
	if (j == i)
		data->end_flag = 1;
	return ;
}
