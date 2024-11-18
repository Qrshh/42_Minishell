/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:00 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 14:26:28 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_env_var_string(t_env *env, char *name, char *value)
{
	char	*new_var;
	int		name_len;
	int		value_len;
	int		i;

	i = 0;
	name_len = ft_strlen(name);
	if (value != NULL)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	new_var = malloc(sizeof(int) * (name_len + value_len + 2));
	if (!new_var)
		return (NULL);
	if (is_valid_name(name, name_len))
		return (NULL);
	ft_strcpy(new_var, name);
	if (value_len > 0 || env->equal == 0)
	{
		new_var[name_len] = '=';
		ft_strcpy(new_var + name_len + 1, value);
	}
	return (new_var);
}

int	update_var(t_env *env, char *name, char *value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env->env_cpy[i])
	{
		if (ft_strncmp(env->env_cpy[i], name, ft_strlen(name)) == 0
			&& (env->env_cpy[i][name_len] == '='
			|| env->env_cpy[i][name_len] == '\0'))
		{
			if (value == NULL && env->env_cpy[i][name_len] == '=')
				return (0);
			return (update_or_create_var(env, &env->env_cpy[i], name, value));
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
	new_env_cpy[count] = create_env_var_string(env, name, value);
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
	char	*name;
	char	*value;
	int		update_result;

	i = 1;
	while (cmd->args[i])
	{
		if (extract_name_value(cmd->args[i], &name, &value, env))
			return (1);
		update_result = update_var(env, name, value);
		if (update_result == -1)
		{
			if (value == NULL)
				add_new_var(env, name, "");
			else
				add_new_var(env, name, value);
		}
		free(name);
		if (value != NULL)
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
