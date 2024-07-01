/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/01 15:06:54 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, t_philo *p)
{
	pthread_mutex_lock(fork);
	if (flag_check(p->end_flag) == DOWN)
		safe_printf("has taken a fork", get_time(p->time), p);
	return ;
}

int	thinking(t_philo *philo, int i)
{
	safe_printf("is thinking", get_time(philo->time), philo);
	if (i == 1 && philo->nb % 2 == 0)
	{
		usleep(philo->eat_time / 2);
	}
	lock(philo->l_fork, philo);
	if (flag_check(philo->end_flag) == UP || philo->l_fork == philo->r_fork)
	{
		return (pthread_mutex_unlock(philo->l_fork), ERROR);
	}
	lock(philo->r_fork, philo);
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	long	time;

	time = get_time(philo->time);
	val_set(&philo->time_of_last_meal, time);
	if (flag_check(philo->end_flag) == UP)
		return (unlock_both(philo), ERROR);
	safe_printf("is eating", time, philo);
	if (philo->times_must_eat > 0)
	{
		philo->times_must_eat--;
	}
	if (philo->eat_time == 0)
		usleep(100);
	usleep(philo->eat_time);
	if (philo->times_must_eat == 0)
	{
		flag_set(&philo->local_end, 1);
	}
	unlock_both(philo);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	safe_printf("is sleeping", get_time(philo->time), philo);
	if (philo->sleep_time == 0)
		usleep(100);
	else
		usleep(philo->sleep_time);
	return (SUCCESS);
}
