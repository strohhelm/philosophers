/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safety_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:32:58 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/24 14:32:37 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	val_set(t_value *to_change, long amount)
{
	pthread_mutex_lock(&to_change->lock);
	to_change->value = amount;
	pthread_mutex_unlock(&to_change->lock);
	return ;
}

int	val_comp(t_value *to_check, long against)
{
	pthread_mutex_lock(&to_check->lock);
	if (to_check->value == against)
		return (pthread_mutex_unlock(&to_check->lock), EQUAL);
	else if (to_check->value < against)
		return (pthread_mutex_unlock(&to_check->lock), SMALLER);
	else
		return (pthread_mutex_unlock(&to_check->lock), BIGGER);
}

int	val_get(t_value *value)
{
	long	tmp;

	pthread_mutex_lock(&value->lock);
	tmp = value->value;
	pthread_mutex_unlock(&value->lock);
	return (tmp);
}

int	flag_check(t_value *flag)
{
	pthread_mutex_lock(&flag->lock);
	if (flag->value == 0)
		return (pthread_mutex_unlock(&flag->lock), DOWN);
	return (pthread_mutex_unlock(&flag->lock), UP);
}

void	flag_set(t_value *flag, int value)
{
	pthread_mutex_lock(&flag->lock);
	flag->value = value;
	pthread_mutex_unlock(&flag->lock);
}
