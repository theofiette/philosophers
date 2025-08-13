/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:22:37 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/10 15:15:44 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void empty_data(t_init *init)
{
	init->pid_tab = NULL;
	init->sem_ready = NULL;
	init->sem_forks = NULL;
	init->sem_stop = NULL;
}

void	init_data(t_args *args, t_init *init)
{
	int i;

	i = 0;
	empty_data(init);
	init->pid_tab = malloc(sizeof(pid_t*) * (args->philo_nbr + 1));
	if (init->pid_tab == NULL)
		failure_exit("Failed malloc of pid_tab\n", 1, init);
	while (i <= args->philo_nbr)
	{
		init->pid_tab[i] = 0;
		i ++;
	}
	init->sem_ready = sem_open(SEM_READY, O_CREAT | O_EXCL, 0666, 0);
	if (init->sem_ready == NULL || init->sem_ready == SEM_FAILED)
			failure_exit("Failed open of " SEM_READY, 1, init);
	init->sem_forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0666, args->philo_nbr / 2);
	if (init->sem_forks == NULL || init->sem_forks == SEM_FAILED)
			failure_exit("Failed open of " SEM_FORKS, 1, init);
	init->sem_stop = sem_open(SEM_STOP, O_CREAT | O_EXCL, 0666, 0);
	if (init->sem_stop == NULL || init->sem_stop == SEM_FAILED)
			failure_exit("Failed open of " SEM_STOP, 1, init);
}

void	fill_philo(t_args *args, t_init *init, t_philo *philo)
{
	philo->id = 0;
	philo->state = STATE_THINKING;
	philo->forks = 0;
	philo->meal_done = 0;
	philo->meal_nbr = args->meal_nbr;
	philo->time_to_die = args->time_to_die;
	philo->time_to_eat = args->time_to_eat;
	philo->time_to_sleep = args->time_to_sleep;
	philo->time_last_eat = 0;
	philo->show = args->show;
	philo->sem_ready = init->sem_ready;
	philo->sem_forks = init->sem_forks;
	philo->sem_stop = init->sem_stop;
	philo->alone = FALSE;
}
