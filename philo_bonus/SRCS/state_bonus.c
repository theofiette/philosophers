/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:43:41 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 10:19:31 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	state_print(suseconds_t time, t_philo *philo)
{
	time = get_time(&philo->time, philo->start_time);
	sem_wait(philo->sem_print);
	if (philo->state == STATE_DYING)
	{
		printf("%ld %d died\n", time, philo->id);
		return ;
	}
	else if (philo->state == STATE_TAKING)
		printf("%ld %d has taken a fork\n", time, philo->id);
	else if (philo->state == STATE_EATING)
		printf("%ld %d is eating\n", time, philo->id);
	else if (philo->state == STATE_SLEEPING)
		printf("%ld %d is sleeping\n", time, philo->id);
	else if (philo->state == STATE_THINKING)
		printf("%ld %d is thinking\n", time, philo->id);
	sem_post(philo->sem_print);
	usleep(100);
}

// void	state_print(suseconds_t time, t_philo *philo)
// {
// 	// time = get_time(&philo->time, philo->start_time);
// 	sem_wait(philo->sem_print);
// 	time = get_time(&philo->time, philo->start_time);
// 	if (philo->state == STATE_DYING)
// 	{
// 		printf("%s%ld %d died\n", philo->color, time, philo->id);
// 		return ;
// 	}
// 	else if (philo->state == STATE_TAKING)
// 		printf("%s%ld %d has taken a fork\n", philo->color, time, philo->id);
// 	else if (philo->state == STATE_EATING)
// 	{
// 		printf("%s%ld %d is eating", philo->color, time, philo->id);
// 		if (philo->show)
// 			printf(" meal number [%d / %d]", philo->meal_done + 1,
// 				philo->meal_nbr);
// 		printf("\n");
// 	}
// 	else if (philo->state == STATE_SLEEPING)
// 		printf("%s%ld %d is sleeping\n", philo->color, time, philo->id);
// 	else if (philo->state == STATE_THINKING)
// 		printf("%s%ld %d is thinking\n", philo->color, time, philo->id);
// 	printf("\e[0m");
// 	sem_post(philo->sem_print);
// 	usleep(100);
// }

void	switch_state(t_philo *philo, int new_state, suseconds_t time)
{
	philo->state = new_state;
	if (new_state == STATE_STOP)
	return ;
	time = get_time(&philo->time, philo->start_time);
	state_print(time, philo);
	if (new_state == STATE_THINKING)
	{
		if (philo->time_to_eat >= philo->time_to_sleep)
		{
			usleep(100);
		}
	}
	if (new_state == STATE_EATING)
	{
		philo->time_start_eat = time;
	}
	if (new_state == STATE_SLEEPING)
	{
		// SEMAPHORE
		while (philo->forks)
		{
			sem_post(philo->sem_forks);
			philo->forks --;
		}
		philo->time_start_sleep = time;
	}
}

static void	_state_taking(t_philo *philo, suseconds_t time)
{
	state_print(time, philo);
	// SEMAPHORE	
	// sem_wait(philo->sem_forks);
	// philo->forks ++;
	switch_state(philo, STATE_EATING, time);
}

static void	_state_eating(t_philo *philo, suseconds_t time)
{
	if (time - philo->time_start_eat >= philo->time_to_eat)
	{
		philo->meal_done ++;
		if (philo->meal_nbr && philo->meal_done == philo->meal_nbr)
			switch_state(philo, STATE_STOP, time);
		else
			switch_state(philo, STATE_SLEEPING, time);
	}
	usleep(100);
}

static void	_state_sleeping(t_philo *philo, suseconds_t time)
{
	if (philo->state == STATE_DYING)
		return ;
	if (time - philo->time_start_sleep >= philo->time_to_sleep)
	{
		switch_state(philo, STATE_THINKING, time);
	}
	usleep(100);
}

static void	_state_thinking(t_philo *philo, suseconds_t time)
{
	if (philo->alone)
	{
		philo->state = STATE_TAKING;
		state_print(time, philo);
		usleep(philo->time_to_die * 1000);
		switch_state(philo, STATE_DYING, time);
	}
	else
	{
		if (philo->meal_done && (philo->time_to_die <= philo->time_to_eat * (2 + philo->odd)))
		{
			usleep(100);
			return ;
		}
		sem_wait(philo->sem_forks);
		philo->forks ++;
		switch_state(philo, STATE_TAKING, time);
	}
		
}

void	_state_machine(t_philo *philo, suseconds_t time)
{
	if (philo->state == STATE_THINKING)
		_state_thinking(philo, time);
	else if (philo->state == STATE_TAKING)
		_state_taking(philo, time);
	else if (philo->state == STATE_EATING)
		_state_eating(philo, time);
	else if (philo->state == STATE_SLEEPING)
		_state_sleeping(philo, time);
}
