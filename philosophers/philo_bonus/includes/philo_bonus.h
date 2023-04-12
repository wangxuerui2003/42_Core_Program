/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:31:10 by wxuerui           #+#    #+#             */
/*   Updated: 2023/04/11 19:05:57 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <signal.h>

// Error Messages
# define EMSG_USAGE "Usage: ./philo num_philo t_die t_eat t_sleep [must_eat]"
# define EMSG_INVALID_ARG "Invalid argument."
# define EMSG_MEMORY "Malloc failed."
# define EMSG_SEM_OPEN "sem_open failed."
# define EMSG_SEM_CLOSE "sem_close failed."
# define EMSG_SEM_UNLINK "sem_unlink failed."
# define EMSG_T_CREATE "pthread_create failed."
# define EMSG_T_JOIN "pthread_join failed."
# define EMSG_T_DETACH "pthread_detach failed."

/*Colours*/
# define BOLD		"\x1b[1m"
# define RED		"\x1b[31m"
# define GREEN 		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

enum e_philo_state {
	EATING,
	THINKING,
	SLEEPING,
	WAITING,
	DIED
};

typedef struct timeval	t_timeval;

typedef struct s_args {
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	t_timeval		start_time;
	sem_t			*start_simulation;
	sem_t			*sem_print;
	sem_t			*eat_protector;
}	t_args;

typedef struct s_philo {
	int			id;
	pid_t		pid;
	int			times_ate;
	t_timeval	last_eat;
	t_args		*args;
}	t_philo;

// Functions
t_args	*take_input(int ac, char **av);
int		ft_atoi(char *str);
int		ft_isposint(char *str);
sem_t	*create_forks(t_args *args);
t_philo	*init_simulation(t_args *args, sem_t *forks);
void	philosophizing(t_args *args, sem_t *forks, int id);
int		check_death(t_philo *args);
void	philo_talk(t_philo *philo, int philo_state);
void	error_exit(char *msg);
void	start_simulation(t_args *args);

#endif