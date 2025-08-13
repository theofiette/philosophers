/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:16:39 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 15:59:18 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers_bonus.h"

static void parse(t_args *args, int argc, char **argv)
{
	check_usage(argc, argv);
	check_values(argv);
	fill_args(args, argc, argv);
}

static void	_end_check(t_philo *philo, suseconds_t time)
{
	if (philo->state == STATE_STOP)
		return ;
	if (time - philo->time_start_eat >= philo->time_to_die)
		switch_state(philo, STATE_DYING, time);
}

void	child_process(t_init *init, t_philo *philo, int philo_id)
{
	suseconds_t	time;
	
	philo->id = philo_id;
	get_color(philo_id, philo);
	synchronize(init, philo);
	while (philo->state != STATE_DYING && philo->state != STATE_STOP)
	{
		time = get_time(&(philo->time), philo->start_time);
		_end_check(philo, time);
		_state_machine(philo, time);
	}
	while (philo->forks)
	{
		sem_post(philo->sem_forks);
		philo->forks --;
	}
	child_clean_init(init); 
	exit(philo->state);
}

void	fork_management(t_args *args, t_init *init, t_philo *philo)
{
	int fork_id;
	int philo_id;

	philo_id = 1;
	while (philo_id <= args->philo_nbr)
	{
		fork_id = fork();
		if (fork_id == -1)
		{
			failure_exit("Failed to fork!\n", 1, init);
		}
		else if (!fork_id)
		{
			if (args->philo_nbr == 1)
				philo->alone = TRUE;
			child_process(init, philo, philo_id);
		}
		init->pid_tab[philo_id -1] = fork_id;
		philo_id ++;
	}
}

static void	kill_all_children(t_init *init)
{
	int i;

	i = 0;
	if (init->pid_tab)
	{
		while (init->pid_tab[i])
		{
			if (!waitpid(init->pid_tab[i], NULL, WNOHANG))
			{
				kill(init->pid_tab[i], SIGKILL);
				init->pid_tab[i] = 0;
			}
			i ++;
		}
	}
}

void	wait_for_children(t_args *args, t_init *init)
{
	int i;
	int	status;

	i = 1;
	while (i <= args->philo_nbr)
	{
		waitpid(0, &status, 0);
		if (status == DEATH_STATUS)
		{
			kill_all_children(init);
			break ;
		}
		i ++;
	}
	return ;
}

int main(int argc, char **argv)
{
	t_args	args;
	t_init	init;
	t_philo	philo;

	parse(&args, argc, argv);
	init_data(&args, &init);
	fill_philo(&args, &init, &philo);
	fork_management(&args, &init, &philo);
	sem_post(init.sem_ready);
	wait_for_children(&args, &init);
	clean_init(&init);
	return (0);
}
