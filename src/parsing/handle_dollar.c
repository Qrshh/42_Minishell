/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:06 by ozdemir           #+#    #+#             */
/*   Updated: 2024/09/30 16:43:49 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*replace_var(char *input, char *var_name, char *var_value)
{
	int		i;
	int		new_len;
	char	*new_input;
	char	*pos;

	i = 0;
	new_len = ft_strlen(input) - ft_strlen(var_name) + ft_strlen(var_value);
	new_input = malloc(sizeof(char) * new_len + 1);
	if (!new_input)
		return (NULL);
	pos = ft_strstr(input, var_name);
	if (pos)
	{
		ft_strncpy(new_input, input, pos - input);
		new_input[pos - input] = '\0';
		ft_strcat(new_input, var_value);
		ft_strcat(new_input, pos + strlen(var_name));
	}
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
	return ("");
}

char	*handle_dollar(char *input, t_env *env)
{
	int		i;
	char	*new_input;
	char	*var_name;
	char	*var_value;
	char	*dollar_var_name;

	i = 0;
	new_input = ft_strdup(input);
	if (!new_input)
		return (NULL);
	while (new_input[i])
	{
		if (new_input[i] == '$')
		{
			var_name = get_var_name(&new_input[i + 1]);
			var_value = find_var_value(env, var_name);
			if (var_value)
			{
				dollar_var_name = ft_strjoin("$", var_name);
				new_input = replace_var(new_input, dollar_var_name, var_value);
				free(dollar_var_name);
				i += ft_strlen(var_value) - 1;
			}
			else
			{
				i++;
			}
			free(var_name);
		}
		else
			i++;
	}
	free(input);
	return (new_input);
}
