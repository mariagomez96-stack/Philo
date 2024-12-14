/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marigome <marigome@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 08:59:15 by marigome          #+#    #+#             */
/*   Updated: 2024/12/14 11:37:23 by marigome         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Libraries

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>   // Para waitpid()
# include <fcntl.h>      // Para O_CREAT y O_EXCL
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>
# include <signal.h> // Para usar señales como SIGKILL

# define THINK "is thinking"
# define INTMIN -2147483648
# define INTMAX 2147483647
# define UNLOCK 1
# define LOCK 0
# define TAKEN_FORK "has taken a fork"
# define SLEEP "is sleeping"
# define DEAD "is dead"
# define EAT "is eating"

# define USAGE_ERR			"❗Arguments: Usage: ./philo <Nbr philosophers> \
<time to die> <time to eat> <time to sleep> [Nbr times each philosopher must \
eat]"
# define NUM_ARGV_ERR		"❗1️⃣ Incorrect number of arguments, expected min 4\
 o max 5."
# define NO_INT_ARGV_ERR	"❗Argument is not integer value"
# define INT_NEG_ARGV_ERR	"❗Argument with negativ integer value. Forbidden."
# define PARAMS_ERR			"❗Incorrect parameteres."
# define ARG				"Argument "
# define INVALID			" is not valid."
# define NEGATIVE			" negative value."
# define VALUES_INVALID		"Values of some parameter are invalid."
# define INIT_ERR			"Initialization error."
# define THREADS_ERR		"Threads error."
# define BYE				"Fix the argument, my friend."

/* t_philo    : Structure of caracteristics and
				state of each philo
*/

typedef struct s_philo
{
	int				pos;
	int				times_eaten;
	// int				right_fork;
	// int				left_fork;
	unsigned long	last_meal;
	char			*pos_char;
	struct s_envp	*envp;
}					t_philo;

typedef struct s_envp
{
	int				nbr_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_limit;
	int				eat_max;
	int				stopping_rule;
	unsigned long	init_time;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*mealtime;
	sem_t			writing;
}					t_envp;
// INITIALIZATION STRUCTURES

int	ft_init_semaphores(t_envp *envp);
int	ft_init_philo(t_envp *envp);
int	ft_init_sim(t_envp *envp);
void	ft_init_struct(t_envp *envp, int argc, char *argv[]);



void	ft_check_eat(t_philo *philo);
void	ft_check_stamp(char *msg, t_philo *philo, int unlock);
void	ft_check_dead(t_envp *envp, t_philo *philo);
void	ft_destroy_semaphores_and_free(t_envp *envp);
int	ft_check_params(t_envp *envp, int argc, char *argv[]);

void	ft_manage_err_simple(const char *err);
void	ft_manage_err(const char *err);
int	ft_isinteger(char *nbr);
int	ft_is_int(char *nptr);
void	ft_sleep(unsigned long total_time, t_envp *envp);
unsigned long	ft_get_time(void);
int	ft_philo_atoi(const char *nptr);
char	*ft_philo_itoa(int n);

#endif