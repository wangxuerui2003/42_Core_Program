/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxuerui <wxuerui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 11:11:18 by wxuerui           #+#    #+#             */
/*   Updated: 2023/02/28 15:40:41 by wxuerui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define ERR_ARGS "Usage: n_philosophers ms_die ms_eat ms_sleep [n_eat]"
# define ERR_VAL "Error: All arguments should be positive integers!"
# define ERR_UNKNOWN "Error: An unknown error happened."

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

enum e_sim_state {
	DOING,
	DONE
};

typedef struct s_args {
	int					input[5];
	enum e_sim_state	sim_state;
	pthread_mutex_t		printer_lock;
	pthread_mutex_t		statecheck_lock;
	struct timeval		start_time;
	pthread_mutex_t		eat_protector;
	pthread_mutex_t		deathcheck_lock;
	int					eat_left;
}	t_args;

enum e_args_index {
	N_PHILO,
	MS_DIE,
	MS_EAT,
	MS_SLEEP,
	N_EAT
};

typedef struct s_philosopher {
	int				id;
	pthread_t		tid;
	pthread_t		checker_tid;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_args			*args;
	struct timeval	last_eat;
	pthread_mutex_t	checker_lock;
	int				n_eat;
}	t_philosopher;

int				error_output(char *msg);
int				ft_atoi(char *str);
bool			init_args(t_args *args, int ac, char **av);
bool			ft_isposint(char *num);
t_philosopher	*init_philosophers(t_args *args, pthread_mutex_t *forks);
pthread_mutex_t	*init_forks(t_args *args);
bool			init_args(t_args *args, int ac, char **av);
bool			start_routine(t_philosopher *philosophers, t_args *args);
void			philo_talk(t_philosopher *philosopher, int philo_state);
int				get_sim_state(t_args *args);
void			update_sim_state(t_args *args, int state);
void			*philo_routine(void *arg);
void			*checker_routine(void *arg);

#endif