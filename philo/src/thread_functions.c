/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/18 17:50:42 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, int nb, t_mutex *p_lock)
{
	pthread_mutex_lock(fork);
	safe_printf("has taken a fork", get_time(), nb, p_lock);
	return ;
}

void	think(t_philo *philo, long wait)
{
	safe_printf("is thinking", get_time(), philo->nb, philo->p_lock);
	usleep(wait);
	if (*(philo->end_flag) != 0)
		return ;
	lock(philo->l_fork, philo->nb, philo->p_lock);
	if (*(philo->end_flag) != 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	lock(philo->r_fork, philo->nb, philo->p_lock);
	if (*(philo->end_flag) != 0)
	{
		unlock_both(philo);
		return ;
	}
	return ;
}

void	eat(t_philo *philo, int *local_end)
{
	int		sleep_check;

	safe_printf("is eating", get_time(), philo->nb, philo->p_lock);
	philo->time_of_death += philo->time_to_die;
	sleep_check = usleep(philo->eat_time);
	unlock_both(philo);
	if (philo->times_must_eat > 0)
		philo->times_must_eat--;
	if (philo->times_must_eat == 0 || sleep_check < 0)
		*local_end = 1;
}

int	ft_sleep(t_philo *philo)
{
	safe_printf("is sleeping", get_time(), philo->nb, philo->p_lock);
	if (*(philo->end_flag) == 0)
	{
		usleep(philo->sleep_time);
		return (1);
	}
	return (0);
}
