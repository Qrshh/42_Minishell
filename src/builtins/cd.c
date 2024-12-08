/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:58:31 by qrshh             #+#    #+#             */
/*   Updated: 2024/11/18 17:26:07 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(t_env *env, char *var_name, char *value, t_arena *arena)
{
	int	i;
	int	len;

	len = ft_strlen(var_name);
	i = 0;
	while (env->env_cpy[i])
	{
		if (ft_strncmp(env->env_cpy[i], var_name, len) == 0
			&& env->env_cpy[i][len] == '=')
		{
			env->env_cpy[i] = aft_strjoin(var_name, "=", arena);
			env->env_cpy[i] = aft_strjoin(env->env_cpy[i], value, arena);
			return ;
		}
		i++;
	}
}

int	my_cd(t_cmd *cmd, t_env *env, t_arena *arena)
{
	char	*home;
	char	*old_pwd;
	char	*new_pwd;

	if (cmd->args[1] && cmd->args[2])
		return (printf("cd : too many arguments\n"), 1);
	old_pwd = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		home = find_var_value(env, "HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (printf("cd: no such file or dir: %s\n", home), 1);
	}
	else if (chdir(cmd->args[1]) != 0)
		return (printf("cd: no such file or dir: %s\n", cmd->args[1]), 1);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_path(env, "OLDPWD", old_pwd, arena);
		update_path(env, "PWD", new_pwd, arena);
	}
	return (0);
}
