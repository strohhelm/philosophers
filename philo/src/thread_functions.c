/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/02 18:41:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, t_philo *p)
{
	pthread_mutex_lock(fork);
	if (flag_check(p->end_flag) == DOWN)
	{
		safe_printf("has taken a fork", get_time(p->time), p, DOWN);
	}
	return ;
}

void	unlock_both(t_philo *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

int	thinking(t_philo *philo, int i)
{
	long	time;

	time = get_time(philo->time);
	safe_printf("is thinking", time, philo, DOWN);
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
	safe_printf("is eating", time, philo, DOWN);
	if (philo->times_must_eat > 0)
	{
		philo->times_must_eat--;
	}
	if (philo->eat_time == 0)
		usleep(100);
	else
	{
		while (get_time(philo->time) - time <= philo->eat_time)
			usleep(1);
	}
	if (philo->times_must_eat == 0)
	{
		flag_set(&philo->local_end, 1);
	}
	unlock_both(philo);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	long	time;

	time = get_time(philo->time);
	safe_printf("is sleeping", time, philo, DOWN);
	if (philo->sleep_time == 0)
		usleep(100);
	else
		while ((get_time(philo->time) - time) <= philo->sleep_time)
			usleep(1);
	return (SUCCESS);
}
