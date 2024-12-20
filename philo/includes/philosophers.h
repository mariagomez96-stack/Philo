/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:59:15 by marigome          #+#    #+#             */
/*   Updated: 2024/12/20 20:15:48 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Libraries

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# define THINK "is thinking"
# define INTMIN -2147483648
# define INTMAX 2147483647
# define UNLOCK 1
# define LOCK 0
# define TAKEN_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define DEAD "is dead"
# define EAT "is eating"

/* t_philo    : Structure of caracteristics and
				state of each philo
*/

typedef struct s_philo
{
	int				id;				// Position of the philo at table (ID)
	int				left_fork;		// Position of the left fork	
	int				right_fork;		// Position of the right fork
	int				eat_count;		// Number of times the philo has eaten
	unsigned long	last_eat;		// Time of the last meal
	char			*status;		// ID char
	int		        last_time_status;
	pthread_t		thread_id;		// ID of the thread (hilo)
	pthread_mutex_t eat_count_mutex;
	struct s_data	*data;			// Pointer to the data structure
}	t_philo;

/* t_data      : Globar environment of the program. It contains
				 the params, share resources (mutexes) 
				 and a reference to philos*/

typedef struct s_data
{
	int				philo_count;	// Number of philosophers
	int				time_to_die;	// Max time without eating (To die)
	int				time_to_eat;	// Time that a philo takes to eat
	int				time_to_sleep;	// Time that a philo takes to sleep
	int				time_to_think;
	int				eat_count_max;	// Total of meals that philos has eaten
	int				max_ate;		// Max eats of each philo
	int				stopping;		// Flag to stop the simulation
	unsigned long	start;			// Time when the simulation starts
	pthread_mutex_t	*forks;			// Array of mutexes to represent the forks
	pthread_mutex_t	print;			// Mutex to print the status of the philos
	pthread_mutex_t	mealtime;		// Mutex to control the time of the meals
	pthread_mutex_t stopping_mutex;
	pthread_mutex_t mutex_max_ate;
	t_philo			*philos;		// Array of philos
}	t_data;

// INITIALIZATION STRUCTURES

void			ft_init_env(t_data *env, int argc, char *argv[]);
int				ft_init_philos(t_data *env);

// INITIALIZATION MUTEX

/* ft_init_mutex:     Initialization of mutex for params which needs.
					** Pthreads Library: pthread_mutex_init **
					- forks
					- print
					- mealtime 
*/
int				ft_init_mutex(t_data *env);

/* ft_init_philo_sim:  Initialization of resources for philos simulation
					- env->philos: Array of philos
					- env->forks: Array of mutexes
					- Init_mutex
					- Init philo
*/
int				ft_init_philo_sim(t_data *env);

// FREE
void			ft_free_philo(t_data *data);

// UTILS
int				ft_atoi(const char *str);
unsigned int	ft_count_digits(int n);
char			*ft_itoa(int n);
void			ft_destroy_mutex(t_data *data);

// CHECKER
int				ft_is_int(char *str);
int				ft_check_args(t_data *env, int argc, char **argv);

// UTILS PHILOS
void			ft_sleep(unsigned long time, t_data *data);
unsigned long	ft_get_time(void);
void			ft_dead(t_data *data, t_philo *philo);
void			ft_check_status(char *mesg, t_philo *philo, int lock);
void			ft_eat(t_philo *philo);
void			ft_think(unsigned long time, t_data *data);

// UTILS THREADS
int				ft_lock_stop_flag(t_data *data);
void			ft_check_dead_flag(t_philo *philo, t_data *data);
void			ft_lock_mutex_ate(t_data *data, int i);
void			ft_check_max_eat(t_data *data, t_philo *philo);
void			ft_dead_util(t_philo *philo, t_data *data, int i);
int				ft_ate_flag(t_data *data);

// THREATS
int				ft_thread(t_data *data);
int				ft_strcmp(const char *s1, const char *s2);

#endif