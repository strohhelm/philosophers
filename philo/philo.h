/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:12:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/15 13:57:06 by pstrohal         ###   ########.fr       */
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
	ERR,
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
	int			times_must_eat;
	t_value		time_of_last_meal;
	t_value		*end_flag;
	t_value		*finished;
	t_mutex		*print;
}	t_philo;

typedef struct s_input {
	int			nb_of_philos;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			times_must_eat;
	t_mutex		print;
	t_mutex		*forks;
	int			*fork_init;
	t_philo		*group;
	pthread_t	deathwatch;
	int			deathwatch_init;
	t_value		end_flag;
	t_value		finished;
}	t_input;

/*		allocating_and_initializing		*/

int		allocate_stuff(t_input *data);
int		create_threads(t_input *data);
int		init_group(t_input *data);
int		init_rest_mutexes(t_input *data);

/*		allocating_utils				*/

void	wait_for_creation(t_input *data);
int		*allocate_value_array(int nb_of_philos);
void	zero_mutex_indicators(t_input *data);

/*		destroy_and_free				*/

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

void	lock(pthread_mutex_t *fork, t_philo *p);
void	unlock_both(t_philo *philo);
int		thinking(t_philo *philo, int i);
int		eating(t_philo *philo);
int		sleeping(t_philo *philo);

/*		thread_routines					*/

void	*philos(void *arg);
void	*death_watching(void *arg);

/*		utils							*/
int		ft_atoi(char *str);
int		safe_printf(char *s, t_philo *philo, int i);
long	get_time(void);
void	val_increase(t_value *value);

#endif