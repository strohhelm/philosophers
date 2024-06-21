/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:16:04 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/21 17:46:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_input			data;
	int				i;

	if (!(argc == 5 || argc == 6))
		return (printf("Wrong amount of arguments!\n"), 1);
	if (initialize_input(argc, argv, &data))
		return (printf("INPUT ERROR\n"), 1);
	if (allocate_stuff(&data))
		return (1);
	init_group(&data);
	if (create_threads(&data))
		return (1);
	i = 0;

	ft_free(&data, data.nb_of_philos);
	return (0);
}
