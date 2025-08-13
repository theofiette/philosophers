/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiette <tfiette@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 16:20:46 by tfiette           #+#    #+#             */
/*   Updated: 2025/08/13 16:21:43 by tfiette          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	is_digits(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str ++;
	}
	return (TRUE);
}

int	is_pos_int(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '+' || str[i] == ' ')
		str ++;
	while (str[i] == '0')
		str ++;
	if (!str[i])
		return (FALSE);
	while (str[i])
		i ++;
	if (i < 10)
		return (TRUE);
	if (i > 10)
		return (FALSE);
	if (ft_strcmp(str, "2147483647") > 0)
		return (FALSE);
	return (TRUE);
}
