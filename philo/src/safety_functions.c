/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:32:58 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 17:36:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	value_increase(t_value *to_change, long amount)
{
	pthread_mutex_lock(&to_change->lock);
	to_change->value += amount;
	pthread_mutex_lock(&to_change->lock);
	return ;
}

t_comp	value_compare(t_value *to_check, long against)
{
	pthread_mutex_lock(&to_check->lock);
	if (to_check->value == against)
		return (pthread_mutex_unlock(&to_check->lock), 0);
	if (to_check->value < against)
		return (pthread_mutex_unlock(&to_check->lock), 1);
	if (to_check->value > against)
		return (pthread_mutex_unlock(&to_check->lock), 2);
}

t_flag_state	flag_check(t_value *flag)
{
	pthread_mutex_lock(&flag->lock);
	if (flag->value == 0)
		return (pthread_mutex_unlock(&flag->lock), DOWN);
	if (flag->value == 1)
		return (pthread_mutex_unlock(&flag->lock), UP);
	if (flag->value == -1)
		return (pthread_mutex_unlock(&flag->lock), SIDEWAYS);
	else
		return (pthread_mutex_unlock(&flag->lock), USELESS);
}

void	flag_set(t_value *flag, int value)
{
	pthread_mutex_lock(&flag->lock);
	flag->value = value;
	pthread_mutex_unlock(&flag->lock);
}
