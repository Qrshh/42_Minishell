/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:57:58 by ozdemir           #+#    #+#             */
/*   Updated: 2024/12/09 14:01:17 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_nb(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*aft_itoa(int n, t_arena *arena)
{
	char	*res;
	int		i;
	long	nb;

	i = count_nb(n) - 1;
	nb = n;
	res = arena_alloc(arena, sizeof(char) * (count_nb(n) + 1));
	if (!res)
		return (NULL);
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	if (nb == 0)
		res[0] = '0';
	while (nb != 0)
	{
		res[i] = (nb % 10) + '0';
		i--;
		nb /= 10;
	}
	res[count_nb(n)] = '\0';
	return (res);
}
