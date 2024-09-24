/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:12:38 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/23 16:33:05 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_unset(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	char	*var;
	char	**new_env;

	i = -1;
	j = 0;
	if (!cmd->args[1])
		return (printf("unset: not enough arguments\n"), 1);
	var = cmd->args[1];
	new_env = malloc(sizeof(char *) * count_tab(env->env_cpy));
	if (!new_env)
		return (1);
	while (env->env_cpy[++i])
	{
		if (ft_strncmp(env->env_cpy[i], var, ft_strlen(var)) != 0
			|| env->env_cpy[i][strlen(var)] != '=')
			new_env[j++] = ft_strdup(env->env_cpy[i]);
		else
			free(env->env_cpy[i]);
	}
	new_env[j] = NULL;
	free(env->env_cpy);
	env->env_cpy = new_env;
	return (0);
}
