/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:16:39 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/10 15:12:22 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INCLUDES/philosophers_bonus.h"

static void parse(t_args *args, int argc, char **argv)
{
	check_usage(argc, argv);
	check_values(argv);
	fill_args(args, argc, argv);
}

// void	child_process_clean_init(t_init *init)
// {
// 	int i;

// 	i = 0;
// 	if (init->pid_tab)
// 	{
// 		free(init->pid_tab);
// 	}
// 	if (init->sem_ready && init->sem_ready != SEM_FAILED)
// 	{
// 		sem_unlink(SEM_READY);
// 	}
// 	if (init->sem_forks && init->sem_forks != SEM_FAILED)
// 	{
// 		sem_unlink(SEM_FORKS);
// 	}
// }

// void	*routine(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	sem_wait(philo->sem_stop);
// 	sem_post(philo->sem_stop);
// 	printf("Hello from monitor %d\n", philo->id);
// 	philo->state = STATE_STOP;
// 	// clean exit ?
// 	return (arg);
// }

static void	_end_check(t_philo *philo, suseconds_t time)
{
	// time = get_time(&philo->time, philo->start_time);
	if (philo->state == STATE_STOP)
		return ;
	if (time - philo->time_last_eat >= philo->time_to_die)
		switch_state(philo, STATE_DYING, time);
}

void	child_process(t_init *init, t_philo *philo)
{
	suseconds_t	time;
	// pthread_t	monitor_thread;
	
	// pthread_create(&monitor_thread, 0, &routine, philo);
	synchronize(init, philo);
	while (1)
	{
		sem_wait(philo->sem_ready);
		sem_post(philo->sem_ready);
		if (philo->state == STATE_DYING || philo->state == STATE_STOP)
			break ;			
		time = get_time(&(philo->time), philo->start_time);
		_end_check(philo, time);
		_state_machine(philo, time);
	}
	while (philo->forks)
	{
		sem_post(philo->sem_forks);
		philo->forks --;
	}
	// clean_init(init);
	// pthread_join(monitor_thread, NULL);
	sem_close(philo->sem_ready);
	sem_close(philo->sem_forks);
	sem_close(philo->sem_stop);
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
			philo->id = philo_id;
			get_color(philo_id, philo);
			if (args->philo_nbr == 1)
				philo->alone = TRUE;
			child_process(init, philo);
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
			if (waitpid(init->pid_tab[i], NULL, WNOHANG))
			{
				kill(init->pid_tab[i], SIGTERM);
				init->pid_tab[i] = 0;
			}
			i ++;
		}
		free(init->pid_tab);
		sem_close(init->sem_ready);
		sem_close(init->sem_forks);
		sem_close(init->sem_forks);
		exit (0);
	}
}

/*
*	wait for childs, and can see if child died
*/
void	wait_for_children(t_args *args, t_init *init)
{
	int i;
	int	status;

	i = 1;
	while (i <= args->philo_nbr)
	{
		printf("X\n");
		waitpid(0, &status, 0);
		if (status == DEATH_STATUS)
		{
			sem_wait(init->sem_ready);
			kill_all_children(init);
			sem_post(init->sem_stop);
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
	printf("DONE\n");
	return (0);
}

// LANCER UN THREAD QUI ATTEND DEVANT UN SEMAPHORE POUR DIRE SI DEAD
// car kill va forcement leak

// -> j'ai besoin de pouvoir stop mes process enfants quand un process meurt
// quand je rentre dans un process enfant:
//	-> je cree un thread qui attends devant un semaphore externe et, si il passe :
//		|-> le thread prend le controle du semaphore interne
//		|-> le thread lance le process de sortie (peut-etre juste passer le thread 1 en STATE_STOP)
// si un enfant meurt (wait_pid de n'importe quel process avec un status a DEATH_STATUS) 
// |-> je post le semaphore externe
// |-> les threads child peuvent lancer leur process de stop

// faut il aussi que je rajoute un semaphore pour attendre que tous les process soient ready avant de lancer mon parent_process 