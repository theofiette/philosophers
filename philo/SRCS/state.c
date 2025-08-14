/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 13:05:04 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/14 14:19:51 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	_state_machine(t_philo *philo, suseconds_t time)
{
	if (philo->state == INIT)
		_state_init(philo, time);
	else if (philo->state == TAKING)
		_state_taking(philo, time);
	else if (philo->state == EATING)
		_state_eating(philo, time);
	else if (philo->state == SLEEPING)
		_state_sleeping(philo, time);
	else if (philo->state == THINKING)
		_state_thinking(philo, time);
	else if (philo->state == DYING)
		_state_dying(philo, time);
}

void	switch_state(t_philo *philo, int new_state, suseconds_t time)
{
	philo->state = new_state;
	if (new_state == STOP)
		return ;
	state_print(time, philo);
	if (new_state == EATING)
	{
		philo->time_last_eat = time;
		philo->time_start_eat = time;
	}
	if (new_state == SLEEPING)
	{
		pthread_mutex_lock(philo->forks[philo->fork_first]);
		*philo->fork_state[philo->fork_first] = FREE;
		philo->lock_first = FALSE;
		pthread_mutex_unlock(philo->forks[philo->fork_first]);
		pthread_mutex_lock(philo->forks[philo->fork_second]);
		*philo->fork_state[philo->fork_second] = FREE;
		philo->lock_second = FALSE;
		pthread_mutex_unlock(philo->forks[philo->fork_second]);
		philo->time_start_sleep = time;
	}
}

void	state_print(suseconds_t time, t_philo *philo)
{
	pthread_mutex_lock(philo->ready_mutex);
	time = get_time(&philo->time, philo->start_time);
	if (*philo->ready == FALSE)
		philo->state = STOP;
	else if (philo->state == DYING)
	{
		printf("%s%ld %d died\n", philo->color, time, philo->id);
		*philo->ready = FALSE;
	}
	if (philo->state == TAKING)
		printf("%s%ld %d has taken a fork\n", philo->color, time, philo->id);
	else if (philo->state == EATING)
	{
		printf("%s%ld %d is eating", philo->color, time, philo->id);
		if (philo->show)
			printf(" meal number [%d / %d]", philo->meal_done + 1,
				philo->meal_nbr);
		printf("\n");
	}
	else if (philo->state == SLEEPING)
		printf("%s%ld %d is sleeping\n", philo->color, time, philo->id);
	else if (philo->state == THINKING)
		printf("%s%ld %d is thinking\n", philo->color, time, philo->id);
	printf("\e[0m");
	pthread_mutex_unlock(philo->ready_mutex);
}

// void	state_print(suseconds_t time, t_philo *philo)
// {
// 	pthread_mutex_lock(philo->ready_mutex);
// 	time = get_time(&philo->time, philo->start_time);
// 	if (*philo->ready == FALSE)
// 		philo->state = STOP;
// 	else if (philo->state == DYING)
// 	{
// 		printf("%ld %d died\n", time, philo->id);
// 		*philo->ready = FALSE;
// 	}
// 	if (philo->state == TAKING)
// 		printf("%ld %d has taken a fork\n", time, philo->id);
// 	else if (philo->state == EATING)
// 		printf("%s%ld %d is eating\n", philo->color, time, philo->id);
// 	else if (philo->state == SLEEPING)
// 		printf("%ld %d is sleeping\n", time, philo->id);
// 	else if (philo->state == THINKING)
// 		printf("%ld %d is thinking\n", time, philo->id);
// 	pthread_mutex_unlock(philo->ready_mutex);
// }

void	_state_init(t_philo *philo, suseconds_t time)
{
	philo->time_last_eat = time;
	philo->time_start_sleep = time;
	philo->time_last_sleep = time;
	philo->time_start_eat = time;
	philo->meal_done = 0;
	philo->fork_first = philo->id % 2;
	philo->fork_second = ((philo->id % 2) == 0);
	philo->lock_first = FALSE;
	philo->lock_second = FALSE;
	philo->state = THINKING;
}

void	_state_dying(t_philo *philo, suseconds_t time)
{
	(void)philo;
	(void)time;
}
