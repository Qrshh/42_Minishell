/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:00 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/18 16:46:14 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_var_string(char *name, char *value)
{
	char	*new_var;
	int		name_len;
	int		value_len;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = malloc(name_len + value_len + 2);
	if (!new_var)
		return (NULL);
	ft_strcpy(new_var, name);
	new_var[name_len] = '=';
	ft_strcpy(new_var + name_len + 1, value);
	return (new_var);
}

int	update_var(char **env_cpy, char *name, char *value)
{
	int		i;
	char	*new_var;

	i = 0;
	while (env_cpy[i])
	{
		if (ft_strncmp(env_cpy[i], name, ft_strlen(name)) == 0
			&& env_cpy[i][strlen(name)] == '=')
		{
			free(env_cpy[i]);
			new_var = create_env_var_string(name, value);
			if (!new_var)
				return (1);
			env_cpy[i] = new_var;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	add_new_var(t_env *env, char *name, char *value)
{
	int		count;
	char	**new_env_cpy;

	count = 0;
	while (env->env_cpy[count])
		count++;
	new_env_cpy = malloc(sizeof(char *) * (count + 2));
	if (!new_env_cpy)
		return (1);
	for (int i = 0; i < count; i++)
	{
		new_env_cpy[i] = env->env_cpy[i];
	}
	new_env_cpy[count] = create_env_var_string(name, value);
	if (!new_env_cpy[count])
	{
		free(new_env_cpy);
		return (1);
	}
	new_env_cpy[count + 1] = NULL;
	free(env->env_cpy);
	env->env_cpy = new_env_cpy;
	return (0);
}

int	handle_export(t_cmd *cmd, t_env *env)
{
	int		i;
	char	*name;
	char	*value;
	int		update_result;

	i = 0;
	while (cmd->args[1][i] && cmd->args[1][i] != '=')
		i++;
	if (!cmd->args[1][i])
	{
		printf("export: usage: export VARIABLE=value\n");
		return (1);
	}
	name = ft_strndup(cmd->args[1], i);
	value = ft_strdup(cmd->args[1] + i + 1);
	if (!name || !value)
		return (1);
	update_result = update_var(env->env_cpy, name, value);
	if (update_result == -1)
		add_new_var(env, name, value);
	free(name);
	free(value);
	return (0);
}

int	my_export(t_cmd *cmd, t_env *env)
{
	int	i;
	int	egal;

	i = 0;
	if (!cmd->args[1])
	{
		sort_tab(env->env_cpy);
		while (env->env_cpy[i])
		{
			egal = ft_strchr(env->env_cpy[i], '=');
			if (egal != -1)
				printf("%.*s=\"%s\"\n", egal, env->env_cpy[i],
					&env->env_cpy[i][egal + 1]);
			else //%.*s affiche une string jusqua * (egal ici)
				printf("%s\n", env->env_cpy[i]);
			i++;
		}
		return (0);
	}
	else
		return (handle_export(cmd, env));
}
