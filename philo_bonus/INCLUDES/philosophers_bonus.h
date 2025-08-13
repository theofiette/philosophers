/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:17:39 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/11 18:51:05 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

//// -headers

#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//// -macros

# define SEM_READY	"ready_sem"
# define SEM_FORKS	"forks_sem"
# define SEM_PRINT	"print_sem"

# define TRUE	1
# define FALSE	0

# define DEATH_STATUS	1024
//// -enums

enum	e_state
{
	STATE_THINKING,
	STATE_TAKING,
	STATE_EATING,
	STATE_SLEEPING,
	STATE_DYING,
	STATE_STOP
};

//// -typedefs

typedef struct s_args
{
	int philo_nbr;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int meal_nbr;
	int show;
}	t_args;

typedef struct s_init
{
	pid_t	*pid_tab;
	sem_t	*sem_ready;
	sem_t	*sem_forks;
	sem_t	*sem_print;
}	t_init;


typedef struct s_philo
{
	int				id;
	int				state;
	int				forks;
	int				meal_nbr;
	int				meal_done;
	struct timeval	time;
	suseconds_t		start_time;
	suseconds_t		time_to_die;
	suseconds_t		time_to_eat;
	suseconds_t		time_to_sleep;
	suseconds_t		time_start_sleep;
	suseconds_t		time_start_eat;
	char			color[11];
	int				show;
	sem_t			*sem_ready;
	sem_t			*sem_forks;
	sem_t			*sem_print;
	int				alone;
	int				odd;
}	t_philo;

//// -prototypes

//color_bonus.c
void		get_color(int color, t_philo *philo);
//exit_bonus.c
void		clean_init(t_init *init);
void		child_clean_init(t_init *init);
void		failure_exit(char *err_str, int err_status, t_init *init);
//init_bonus.c
void		init_data(t_args *args, t_init *init);
void		fill_philo(t_args *args, t_init *init, t_philo *philo);
//parsing_bonus.c
void		check_values(char **argv);
void		check_usage(int argc, char **argv);
void		fill_args(t_args *args, int argc, char **argv);
//state_bonus.c
void		_state_machine(t_philo *philo, suseconds_t time);
void		state_print(suseconds_t time, t_philo *philo);
void		switch_state(t_philo *philo, int new_state, suseconds_t time);
//time_bonus.c
void		synchronize(t_init *init, t_philo *philo);
suseconds_t	get_time(struct timeval *time, suseconds_t start_time);
void		set_time(struct timeval *time, suseconds_t *start_time);

//utils_bonus.c
int			ft_atoi(char *n);
int			ft_strlen(char *str);
int			ft_strcmp(char *str1, char *str2);
char		*ft_get_program_name(char *program);

#endif