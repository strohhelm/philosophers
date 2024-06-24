/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:16:04 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/24 09:20:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char *argv[])
{
	t_input			data;

	if (!(argc == 5 || argc == 6))
		return (printf("Wrong amount of arguments!\n"), 1);
	if (initialize_input(argc, argv, &data) != SUCCESS)
		return (printf("INPUT ERROR\n"), ERROR);
	if (allocate_stuff(&data) != SUCCESS)
		return (ERROR);
	init_group(&data);
	if (create_threads(&data) != SUCCESS)
		return (ERROR);
	if (wait_for_philos(&data) != SUCCESS)
		return (ft_free(&data, data.nb_of_philos), ERROR);
	ft_free(&data, data.nb_of_philos);
	return (SUCCESS);
}
