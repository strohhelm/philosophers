/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:12:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/06/25 20:12:58 by pstrohal         ###   ########.fr       */
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

typedef enum e_compare {
	EQUAL,
	SMALLER,
	BIGGER,
}	t_comp;

typedef enum e_succes {
	SUCCESS,
	ERROR,
	LOCK_ERROR,
}	t_outcome;

typedef enum e_flagstate {
	DOWN,
	UP,
}	t_flag_state;

typedef struct s_protected_value {
	long	value;
	t_mutex	lock;
	int		init_flag;
}	t_value;

typedef struct s_philosopher {
	pthread_t	id;
	int			nb;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	long		eat_time;
	long		sleep_time;
	long		time_to_die;
	t_value		time_of_death;
	int			times_must_eat;
	t_value		*end_flag;
	t_value		local_end;
	long		curr_time;
	t_mutex		*print;
	t_mutex		*time;
}	t_philo;

typedef struct s_input {
	int			nb_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			times_must_eat;
	t_mutex		print;
	t_mutex		time;
	t_mutex		*forks;
	int			*fork_init;
	t_philo		*group;
	pthread_t	deathwatch;
	t_value		end_flag;
}	t_input;

/*		allocating_and_initializing		*/

int		allocate_stuff(t_input *data);
int		create_threads(t_input *data);
void	init_group(t_input *data);
int		init_rest_mutexes(t_input *data);

/*		allocating_utils				*/

void	wait_for_creation(t_input *data);
int		*allocate_value_array(int nb_of_philos);
void	zero_mutex_indicators(t_input *data);

/*		destro_and_free					*/

void	ft_free(t_input *data, int j);
void	p_dest(t_input *data, int i);

/*		input_handling					*/

int		validate_argv(int argc, char **argv);
int		initialize_input(int argc, char **argv, t_input *philos);
int		wait_for_philos(t_input *data);

/*		safety_functions				*/

void	val_set(t_value *to_change, long amount);
int		val_comp(t_value *to_check, long against);
int		val_get(t_value *value);
int		flag_check(t_value *flag);
void	flag_set(t_value *flag, int value);

/*		thread_functions				*/

int		lock(pthread_mutex_t *fork, t_philo *p);
int		thinking(t_philo *philo, int i);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);
int		local_end_check(t_input *data);

/*		thread_routines					*/

void	*philos(void *arg);
void	*death_watching(void *arg);

/*		utils							*/
int		ft_atoi(char *str);
int		safe_printf(char *s, long time, int nb, t_mutex *p_lock);
long	get_time(t_mutex *t_lock);
void	unlock_both(t_philo *philo);

#endif