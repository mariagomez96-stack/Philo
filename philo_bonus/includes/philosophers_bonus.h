/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:59:15 by marigome          #+#    #+#             */
/*   Updated: 2024/12/16 14:01:35 by marigome         ###   ########.fr       */
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

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define THINK "is thinking"
# define INTMIN -2147483648
# define INTMAX 2147483647
# define UNLOCK 1
# define LOCK 0
# define TAKEN_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define DEAD "is dead"
# define EAT "is eating"

# define STR_PROG_NAME	"philo:"
# define STR_USAGE	"%s usage: ./philo <number_of_philosophers> \
<time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n"
# define STR_ERR_INPUT_DIGIT	"%s invalid input: %s: \
not a valid unsigned integer between 0 and 2147483647.\n"
# define STR_ERR_INPUT_POFLOW	"%s invalid input: \
there must be between 1 and %s philosophers.\n"
# define STR_ERR_THREAD	"%s error: Could not create thread.\n"
# define STR_ERR_MALLOC	"%s error: Could not allocate memory.\n"
# define STR_ERR_SEM	"%s error: Could not create semaphore.\n"
# define STR_ERR_FORK	"%s error: Could not fork child.\n"

# define SEM_NAME_FORKS "/philo_global_forks"
# define SEM_NAME_WRITE "/philo_global_write"
# define SEM_NAME_FULL	"/philo_global_full"
# define SEM_NAME_DEAD	"/philo_global_dead"
# define SEM_NAME_STOP	"/philo_global_stop"
# define SEM_NAME_MEAL	"/philo_local_meal_"

# define CHILD_EXIT_ERR_PTHREAD	40
# define CHILD_EXIT_ERR_SEM		41
# define CHILD_EXIT_PHILO_FULL	42
# define CHILD_EXIT_PHILO_DEAD	43

/* t_philo    : Structure of caracteristics and
				state of each philo
*/

typedef struct s_data
{
	time_t			start_time;
	unsigned int	philo_count;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				must_eat_count;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_philo_full;
	unsigned int	philo_full_count;
	sem_t			*sem_philo_dead;
	sem_t			*sem_stop;
	int			stop_sim;
	t_philo			**philos;
	t_philo			*this_philo;
	pid_t			*pids;
	pthread_t		gluttony_reaper;
	pthread_t		famine_reaper;
}	t_data;

typedef struct s_philo
{
	pthread_t			personal_grim_reaper;
	sem_t				*sem_forks;
	sem_t				*sem_write;
	sem_t				*sem_philo_full;
	sem_t				*sem_philo_dead;
	sem_t				*sem_meal;
	char				*sem_meal_name;
	unsigned int		nb_forks_held;
	unsigned int		id;
	unsigned int		times_ate;
	int				ate_enough;
	time_t				last_meal;
	t_data				*table;
}	t_philo;

typedef enum e_status
{
	DIED = 0,
	EATING = 1,
	SLEEPING = 2,
	THINKING = 3,
	GOT_FORK_1 = 4,
	GOT_FORK_2 = 5
}	t_status;

// Utils //
int	ft_msg_err(char *str, int exit);
void	ft_free_philos(t_data *data);
int	ft_free_data(char *str, t_data *data);
char	*ft_strcat(char *dest, const char *src);

// Checker //
int	ft_is_int(char *nptr);
int	ft_check_args(t_data *env, int argc, char **argv);

// Init philo
int	ft_getlen(int n);
t_philo **ft_init_philos(t_data * data);
t_data	*init_table(int ac, char **av, int i);

#endif