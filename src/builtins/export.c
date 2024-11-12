/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:00 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/12 13:44:02 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_var_string(char *name, char *value)
{
	char	*new_var;
	int		name_len;
	int		value_len;
	size_t		i;

	i = 0;
	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = malloc(sizeof(int) * (name_len + value_len + 2));
	if (!new_var)
		return (NULL);
	while (i < ft_strlen(name))
	{
		if (!ft_isalpha(name[i]) && name[i] != '_')
		{
			perror("Syntax error");
			return (NULL);
		}
		i++;
	}
	ft_strcpy(new_var, name);
	if (value_len > 0)
		ft_strcpy(new_var + name_len, value);
	else
		new_var[name_len] = '\0';
	return (new_var);
}

int	update_var(char **env_cpy, char *name, char *value)
{
	int		i;
	char	*new_var;

	i = 0;
	while (env_cpy[i])
	{	
		if (ft_strncmp(env_cpy[i], name, ft_strlen(name)) == 0)
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
	int		i;
	char	**new_env_cpy;

	i = 0;
	count = 0;
	while (env->env_cpy[count])
		count++;
	new_env_cpy = malloc(sizeof(char *) * (count + 2));
	if (!new_env_cpy)
		return (1);
	while (i < count)
	{
		new_env_cpy[i] = env->env_cpy[i];
		i++;
	}
	new_env_cpy[count] = create_env_var_string(name, value);
	if (!new_env_cpy[count])
		return (free(new_env_cpy), 1);
	new_env_cpy[count + 1] = NULL;
	free(env->env_cpy);
	env->env_cpy = new_env_cpy;
	return (0);
}

int	handle_export(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	char	*name;
	char	*value;
	int		update_result;

	i = 1;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[i][j] && cmd->args[i][j] != '=')
			j++;
		name = ft_strndup(cmd->args[i], j);
		value = ft_strdup(cmd->args[i] + j);
		if (!name)
			return (1);
		update_result = update_var(env->env_cpy, name, value);
		if (update_result == -1)
			add_new_var(env, name, value);
		free(name);
		free(value);
		i++;
	}
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
			else
				printf("%s\n", env->env_cpy[i]);
			i++;
		}
		return (0);
	}
	else
		return (handle_export(cmd, env));
}