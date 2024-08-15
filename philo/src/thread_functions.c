/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/05 16:29:27 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, t_philo *p)
{
	pthread_mutex_lock(fork);
	safe_printf("has taken a fork", p, DOWN);
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

	time = get_time();
	if (safe_printf("is thinking", philo, DOWN) == ERROR)
		return (ERROR);
	if (i == 1 && philo->nb % 2 == 0)
	{
		while (get_time() - time <= philo->eat_time / 2)
		{
			if (flag_check(philo->end_flag) == UP)
				return (ERROR);
			usleep(200);
		}
	}
	lock(philo->l_fork, philo);
	if (flag_check(philo->end_flag) == UP || philo->l_fork == philo->r_fork)
		return (pthread_mutex_unlock(philo->l_fork), ERROR);
	lock(philo->r_fork, philo);
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	long	time;

	time = get_time();
	val_set(&philo->time_of_last_meal, time);
	if (safe_printf("is eating", philo, DOWN) == ERROR)
		return (unlock_both(philo), ERROR);
	if (philo->times_must_eat > 0)
		philo->times_must_eat--;
	if (philo->eat_time == 0)
		usleep(100);
	else
	{
		while (get_time() - time <= philo->eat_time)
		{
			if (flag_check(philo->end_flag) == UP)
				return (unlock_both(philo), ERROR);
			usleep(200);
		}
	}
	if (philo->times_must_eat == 0)
		val_increase(philo->finished);
	unlock_both(philo);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	long	time;

	time = get_time();
	safe_printf("is sleeping", philo, DOWN);
	if (philo->sleep_time == 0)
		usleep(100);
	else
	{
		while ((get_time() - time) <= philo->sleep_time)
		{
			if (flag_check(philo->end_flag) == UP)
				return (ERROR);
			usleep(200);
		}
	}
	return (SUCCESS);
}
