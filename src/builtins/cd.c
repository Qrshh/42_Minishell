/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:58:31 by qrshh             #+#    #+#             */
/*   Updated: 2024/09/24 16:15:55 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_path(t_env *env, char *var_name, char *value)
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
			free(env->env_cpy[i]);
			env->env_cpy[i] = ft_strjoin(var_name, "=");
			env->env_cpy[i] = ft_strjoin(env->env_cpy[i], value);
			return ;
		}
		i++;
	}
}

int	my_cd(t_cmd *cmd, t_env *env)
{
	char	*home;
	char	*old_pwd;
	char	*new_pwd;

	if (!cmd->args[1])
	{
		home = getenv("HOME");
		if (!home)
			return (printf("cd: HOME not set\n"), 1);
		if (chdir(home) != 0)
			return (printf("cd: no such file or directory: %s\n", home), 1);
	}
	else
	{
		old_pwd = getenv("PWD");
		if (chdir(cmd->args[1]) != 0)
			return (printf("cd: no such file or directory: %s\n", cmd->args[1]),
				1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		if (old_pwd)
			update_path(env, "OLDPWD", old_pwd);
		update_path(env, "PWD", new_pwd);
		free(new_pwd);
	}
	return (0);
}
