/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:44:49 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 13:02:24 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	_state_taking(t_philo *philo, suseconds_t time)
{
	int	fork_state;

	fork_state = LOCKED;
	if (philo->forks[0] == philo->forks[1])
		return ;
	pthread_mutex_lock(philo->forks[philo->fork_second]);
	fork_state = *philo->fork_state[philo->fork_second];
	if (fork_state == FREE)
		*philo->fork_state[philo->fork_second] = LOCKED;
	pthread_mutex_unlock(philo->forks[philo->fork_second]);
	if (fork_state == FREE)
	{
		philo->lock_second = TRUE;
		state_print(time, philo);
		switch_state(philo, EATING, time);
	}
	else
		usleep(500);
}

void	_state_eating(t_philo *philo, suseconds_t time)
{
	if (time - philo->time_start_eat >= philo->time_to_eat)
	{
		philo->meal_done ++;
		if (philo->meal_nbr && philo->meal_done == philo->meal_nbr)
			switch_state(philo, STOP, time);
		else
			switch_state(philo, SLEEPING, time);
	}
	else
		usleep(500);
}

void	_state_sleeping(t_philo *philo, suseconds_t time)
{
	if (philo->state == STOP || philo->state == DYING)
		return ;
	else if (time - philo->time_start_sleep >= philo->time_to_sleep)
	{
		philo->time_last_sleep = time;
		switch_state(philo, THINKING, time);
		if (philo->odd && (philo->time_to_eat >= philo->time_to_sleep))
			usleep(philo->time_to_eat * 1000);
	}
	else
		usleep(500);
}

void	_state_thinking(t_philo *philo, suseconds_t time)
{
	int	fork_state;

	fork_state = LOCKED;
	pthread_mutex_lock(philo->forks[philo->fork_first]);
	fork_state = *philo->fork_state[philo->fork_first];
	if (fork_state == FREE)
		*philo->fork_state[philo->fork_first] = LOCKED;
	pthread_mutex_unlock(philo->forks[philo->fork_first]);
	if (fork_state == FREE)
	{
		philo->lock_first = TRUE;
		time = get_time(&philo->time, philo->start_time);
		switch_state(philo, TAKING, time);
	}
	else
		usleep(500);
}
