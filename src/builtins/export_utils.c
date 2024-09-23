/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:38:02 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/17 13:39:55 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tab(char **env_cpy)
{
	int	count;

	count = 0;
	while (env_cpy[count])
		count++;
	return (count);
}

void	sort_tab(char **env_cpy)
{
	int i;
	int swapped;
	char *temp;
	int count;

	count = count_tab(env_cpy);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
			{
				temp = env_cpy[i];
				env_cpy[i] = env_cpy[i + 1];
				env_cpy[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}
