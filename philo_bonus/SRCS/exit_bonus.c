/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 19:20:04 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 16:10:47 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	print_error(char *err_str)
{
	int	len;

	len = ft_strlen(err_str);
	write(2, err_str, len);
}

static void	clean_semaphore(t_init *init)
{
	if (init->sem_ready && init->sem_ready != SEM_FAILED)
	{
		sem_close(init->sem_ready);
		sem_unlink(SEM_READY);
	}
	if (init->sem_forks && init->sem_forks != SEM_FAILED)
	{
		sem_close(init->sem_forks);
		sem_unlink(SEM_FORKS);
	}
	if (init->sem_print && init->sem_print != SEM_FAILED)
	{
		sem_close(init->sem_print);
		sem_unlink(SEM_PRINT);
	}
}

void	clean_init(t_init *init)
{
	int	i;

	i = 0;
	if (init->pid_tab)
	{
		while (init->pid_tab[i])
		{
			if (!waitpid(init->pid_tab[i], NULL, WNOHANG))
			{
				kill(init->pid_tab[i], SIGTERM);
				printf("X");
			}
			i ++;
		}
		free(init->pid_tab);
	}
	clean_semaphore(init);
}

void	child_clean_init(t_init *init)
{
	int	i;

	i = 0;
	if (init->pid_tab)
	{
		while (init->pid_tab[i])
		{
			if (!waitpid(init->pid_tab[i], NULL, WNOHANG))
				kill(init->pid_tab[i], SIGKILL);
			i ++;
		}
		free(init->pid_tab);
	}
	if (init->sem_ready && init->sem_ready != SEM_FAILED)
		sem_close(init->sem_ready);
	if (init->sem_forks && init->sem_forks != SEM_FAILED)
		sem_close(init->sem_forks);
	if (init->sem_print && init->sem_print != SEM_FAILED)
		sem_close(init->sem_print);
}

void	failure_exit(char *err_str, int err_status, t_init *init)
{
	print_error(err_str);
	clean_init(init);
	exit(err_status);
}
