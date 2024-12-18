/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:59:15 by marigome          #+#    #+#             */
/*   Updated: 2024/12/18 13:10:28 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Libraries


# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <pthread.h>

// Libraries


# define THINK "is thinking"
# define INTMIN -2147483648
# define INTMAX 2147483647
# define UNLOCK 1
# define LOCK 0
# define TAKEN_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define DEAD "is dead"
# define EAT "is eating"
# define THINK "is thinking"
# define DONE "simulation done"

/* t_philo    : Structure of caracteristics and
				state of each philo
*/

typedef struct s_philo
{
	unsigned int	last_meal;		// Time of the last meal
	unsigned int    next_meal;		// Time of the next meal
	int				id;				// ID of the philo
	int             death;			// Flag to control if the philo is dead
	int				eat_count;		// Number of meals that the philo has eaten
	pid_t			pid;			// ID of the thread (hilo)
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
	int				eat_counter;	// Total of meals that philos has eaten
	int				max_eat;		// Max eats of each philo
	int             current_eat; // Flag to control the max eats
	unsigned long	start;			// Time when the simulation starts
	sem_t	*forks;			// Array of mutexes to represent the forks
	sem_t	*print;			// Mutex to print the status of the philos
	sem_t	*death;			// Mutex to control the death of a philo
	sem_t   *stop;			// Mutex to control the stop of the simulation
	sem_t   *current_eat_lock; // Mutex to control the max eats
	t_philo			*philos;		// Array of philos
}	t_data;


// Init structs

int	ft_init_env(int argc, char **argv, t_data *env);
t_philo	*ft_init_philo(t_data *data);

// Checker

int	ft_is_int(char *nptr);
int	ft_parsing(char **av, t_data *simulation);
int	ft_check_args(t_data *env, int argc, char **argv);
// Utils

int	ft_atoi(char *nptr);
int	ft_error(t_data *data, char *message, int ret);
unsigned int	ft_get_time(void);
void	ft_print_message(char *id, t_philo *philo);

// Manage philos
void	*ft_check_death(void *arg);
void	ft_routine(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_take_fork(t_philo *philo);

// Simulation
void  ft_init_simulation(t_data *data, t_philo *philo);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_destroy_all(t_data *simulation, t_philo *philo);
#endif