/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:06 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/24 15:06:39 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	if (ft_strcmp(str, "?") == 0)
		return (ft_strdup("?"));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*replace_var(char *input, char *var_name, char *var_value)
{
	char	*new_input;
	char	*pos;

	new_input = malloc(sizeof(char) * (ft_strlen(var_value) + 1));
	if (!new_input)
		return (NULL);
	pos = ft_strstr(var_name, input);
	if (pos)
		ft_strncpy(new_input, var_value, ft_strlen(var_value) + 1);
	free(input);
	return (new_input);
}

char	*find_var_value(t_env *env, char *var_name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env->env_cpy[i])
	{
		if (ft_strncmp(env->env_cpy[i], var_name, len) == 0
			&& env->env_cpy[i][len] == '=')
			return (&env->env_cpy[i][len + 1]);
		i++;
	}
	return (NULL);
}

t_word	*handle_dollar(t_all *all, t_env *env)
{
	t_word	*current;
	char	*var_value;
	char	*var_name;
	char	*dollar_var_name;
	char	*exit_status_str;

	current = all->list;
	while (current)
	{
		if (current->token == V_ENV)
		{
			var_name = get_var_name(current->str);
			dollar_var_name = ft_strjoin("$", var_name);
			if (ft_strcmp(var_name, "?") == 0)
			{
				exit_status_str = ft_itoa(g_exit_status);
				current->str = replace_var(current->str, "$?", exit_status_str);
				free(dollar_var_name);
				free(var_name);
				current = current->next;
				continue ;
			}
			var_value = find_var_value(env, var_name);
			if (var_value && ft_strlen(var_value) > 0)
			{
				current->str = replace_var(current->str, dollar_var_name,
						var_value);
			}
			else
				current->str = replace_var(current->str, dollar_var_name, "");
			free(dollar_var_name);
			free(var_name);
		}
		current = current->next;
	}
	return (all->list);
}
