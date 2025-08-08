/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:34:23 by tfiette           #+#    #+#             */
/*   Updated: 2025/07/30 19:16:22 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*	
*	simpler atoi version, I've already check that n is a pos_int
*/
int	ft_atoi(char *n)
{
	int	res;
	int	i;
	int	size;

	i = 0;
	res = 0;
	size = ft_strlen(n);
	while (i < size)
		res = (res * 10) + (n[i ++] - '0');
	return (res);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
	{
		i ++;
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

/*
*	returns argv[0] from last '/'
*/
char	*ft_get_program_name(char *program)
{
	char	*res;
	int		i;
	int		offset;

	i = 0;
	offset = 0;
	while (program[i])
	{
		if (program[i ++] == '/')
			offset = i;
	}
	res = program + offset;
	return (res);
}
