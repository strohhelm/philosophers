/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:12:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/18 17:50:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

// typedef struct timeval {
// 		time_t		tv_sec;		/* seconds since Jan. 1, 1970 */
// 		suseconds_t	tv_usec;	/* and microseconds */
// }	t_time;

typedef pthread_mutex_t	t_mutex;


typedef struct s_philosopher {
	pthread_t	id;
	int			nb;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	long		eat_time;
	long		sleep_time;
	long		time_to_die;
	long		time_of_death;
	int			times_must_eat;
	int			*end_flag;
	t_mutex		*p_lock;
}	t_philo;

typedef struct s_input {
	int			nb_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			times_must_eat;
	t_mutex		p_lock;
	t_mutex		*forks;
	t_philo		*group;
	pthread_t	deathwatch;
	int			end_flag;
}	t_input;


int		initialize_input(int argc, char **argv, t_input *philos);
int		ft_atoi(char *str);
long	get_time(void);
void	ft_free(t_input *data, int j);
int		allocate_stuff(t_input *data);
void	unlock_both(t_philo *philo);
void	think(t_philo *philo, long wait);
void	eat(t_philo *philo, int *local_end);
void	safe_printf(char *s, long time, int nb, t_mutex *p_lock);
int		ft_sleep(t_philo *philo);

#endif