/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:59:19 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/08 18:18:57 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
