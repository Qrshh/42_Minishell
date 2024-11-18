/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:12:38 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 17:08:08 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_without_var(char **env_cpy, char *var, char **new_env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (env_cpy[++i])
	{
		if (ft_strncmp(env_cpy[i], var, ft_strlen(var)) != 0
			|| (env_cpy[i][ft_strlen(var)] != '='
			&& env_cpy[i][ft_strlen(var)] != '\0'))
			new_env[j++] = ft_strdup(env_cpy[i]);
		else
			free(env_cpy[i]);
	}
	return (j);
}

int	my_unset(t_cmd *cmd, t_env *env)
{
	char	*var;
	char	**new_env;
	int		new_env_size;

	if (!cmd->args[1])
		return (0);
	var = cmd->args[1];
	new_env_size = count_tab(env->env_cpy);
	new_env = malloc(sizeof(char *) * new_env_size);
	if (!new_env)
		return (1);
	new_env_size = copy_env_without_var(env->env_cpy, var, new_env);
	new_env[new_env_size] = NULL;
	free(env->env_cpy);
	env->env_cpy = new_env;
	return (0);
}
