/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:45:43 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/15 13:57:20 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(char *str)
{
	int		ms;

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

int	safe_printf(char *s, t_philo *philo, int i)
{
	long	time;
	int		state;

	pthread_mutex_lock(philo->print);
	time = get_time();
	state = ERROR;
	if (i == DOWN && flag_check(philo->end_flag) == DOWN)
	{
		printf("%ld %d %s\n", time / 1000, philo->nb, s);
		state = SUCCESS;
	}
	else if (i == UP)
	{
		printf("%ld %d %s\n", time / 1000, philo->nb, s);
	}
	else if (i == ERR)
	{
		printf("%s\n", s);
	}
	pthread_mutex_unlock(philo->print);
	return (state);
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

void	val_increase(t_value *value)
{
	pthread_mutex_lock(&value->lock);
	value->value += 1;
	pthread_mutex_unlock(&value->lock);
}
