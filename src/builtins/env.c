/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:59:19 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 14:17:51 by ozdemir          ###   ########.fr       */
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

int	my_env(t_cmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
	{
		while (env->env_cpy[i])
		{
			printf("%s\n", env->env_cpy[i]);
			i++;
		}
	}
	return (0);
}
