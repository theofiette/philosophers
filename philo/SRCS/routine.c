/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:17:32 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 18:42:29 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	_end_check(t_philo *philo, suseconds_t time)
{
	(void)time;
	if (philo->state == STOP)
		return ;
	if (time - philo->time_last_eat > philo->time_to_die)
		switch_state(philo, DYING, time);
}

static void	unlock_forks(t_philo *philo)
{
	if (philo->lock_first)
	{
		pthread_mutex_lock(philo->forks[philo->fork_first]);
		*philo->fork_state[philo->fork_first] = FREE;
		pthread_mutex_unlock(philo->forks[philo->fork_first]);
	}
	if (philo->lock_second)
	{
		pthread_mutex_lock(philo->forks[philo->fork_second]);
		*philo->fork_state[philo->fork_second] = FREE;
		pthread_mutex_unlock(philo->forks[philo->fork_second]);
	}
}

void	*routine(void *arg)
{
	t_philo		*philo;
	suseconds_t	time;

	philo = (t_philo *)arg;
	synchronize(philo);
	set_time(&(philo->time), &(philo->start_time));
	if (philo->id % 2)
		usleep(999);
	while (philo->state != DYING && philo->state != STOP)
	{
		time = get_time(&(philo->time), philo->start_time);
		_state_machine(philo, time);
		time = get_time(&(philo->time), philo->start_time);
		_end_check(philo, time);
	}
	unlock_forks(philo);
	return (arg);
}
