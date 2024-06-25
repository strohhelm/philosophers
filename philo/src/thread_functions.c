/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/25 18:05:03 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	lock(pthread_mutex_t *fork, t_philo *p)
{
	int	e;

	e = 0;
	if (pthread_mutex_lock(fork) != SUCCESS)
	{
		flag_set(p->end_flag, 1);
		return (LOCK_ERROR);
	}
	if (flag_check(p->end_flag) == DOWN)
		e = safe_printf("has taken a fork", get_time(p->time), p->nb, p->print);
	if (e == ERROR)
	{
		flag_set(p->end_flag, 1);
		return (ERROR);
	}
	return (SUCCESS);
}

int	thinking(t_philo *philo, int i)
{
	if (safe_printf("is thinking", get_time(philo->time), philo->nb,
			philo->print))
		return (ERROR);
	if (i == 1 && philo->nb % 2 == 0)
	{
		usleep(philo->eat_time / 2);
	}
	if (flag_check(philo->end_flag) == UP)
	{
		return (ERROR);
	}
	if (lock(philo->l_fork, philo) == LOCK_ERROR)
	{
		return (ERROR);
	}
	if (flag_check(philo->end_flag) == UP || philo->l_fork == philo->r_fork)
	{
		return (pthread_mutex_unlock(philo->l_fork), ERROR);
	}
	if (lock(philo->r_fork, philo) == ERROR)
	{
		return (unlock_both(philo), ERROR);
	}
	return (SUCCESS);
}

int	eating(t_philo *philo)
{
	if (flag_check(philo->end_flag) == UP)
		return (unlock_both(philo), ERROR);
	if (philo->times_must_eat > 0)
	{
		philo->times_must_eat--;
	}
	val_set(&philo->time_of_death,
		val_get(&philo->time_of_death) + philo->time_to_die);
	if (flag_check(philo->end_flag) == UP)
	{
		return (unlock_both(philo), ERROR);
	}
	if (safe_printf("is eating", get_time(philo->time), philo->nb,
			philo->print) == ERROR)
		return (unlock_both(philo), ERROR);
	if (philo->times_must_eat == 0)
	{
		flag_set(&philo->local_end, 1);
	}
	usleep(philo->eat_time);
	unlock_both(philo);
	return (SUCCESS);
}

int	sleeping(t_philo *philo)
{
	if (flag_check(philo->end_flag) == UP)
		return (ERROR);
	if (safe_printf("is sleeping", get_time(philo->time),
			philo->nb, philo->print))
	{
		return (ERROR);
	}
	usleep(philo->sleep_time);
	return (SUCCESS);
}
