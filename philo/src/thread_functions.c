/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:06:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/17 19:19:21 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	lock(pthread_mutex_t *fork, int nb)
{
	pthread_mutex_lock(fork);
	printf("%ld %d has taken fork\n", get_time(), nb);
	return ;
}

void	unlock(pthread_mutex_t *fork, int *check)
{
	pthread_mutex_unlock(fork);
	*check = 0;
	printf("unlocked\n");
}

void	unlock_both(t_cutlery *utils)
{
	pthread_mutex_unlock(utils->l_fork);
	pthread_mutex_unlock(utils->r_fork);
}

void	think(t_cutlery *utils, int nb, int *end)
{
	if (utils->l_spoon < utils->r_spoon && *end == 0)
	{
		lock(utils->l_fork, nb);
		lock(utils->r_fork, nb);
	}
	else
	{
		lock(utils->r_fork, nb);
		lock(utils->l_fork, nb);
	}
	return ;
}

void	eat(t_philo *philo, int *local_end)
{
	int		sleep_check;

	printf("%ld %d is eating\n", get_time(), philo->nb);
	philo->time_of_death += philo->time_to_die;
	sleep_check = usleep(philo->eat_time * 1000);
	unlock_both(&philo->u);
	if (philo->times_must_eat > 0)
		philo->times_must_eat--;
	if (philo->times_must_eat == 0 || sleep_check < 0)
		*local_end = 1;
}
