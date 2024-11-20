/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:38:02 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/19 14:41:01 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_tab(char **env_cpy)
{
	int		i;
	int		swapped;
	char	*temp;
	int		count;

	count = count_tab(env_cpy);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(env_cpy[i], env_cpy[i + 1]) > 0)
			{
				temp = env_cpy[i];
				env_cpy[i] = env_cpy[i + 1];
				env_cpy[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}

int	is_valid_name(char *name, int name_len)
{
	int	i;

	i = 0;
	while (i < name_len)
	{
		if (!ft_isalpha(name[i]) && name[i] != '_')
		{
			perror("Syntax error");
			return (1);
		}
		i++;
	}
	return (0);
}

int	update_or_create_var(t_env *env, char **env_cpy, char *name, char *value)
{
	free(*env_cpy);
	if (value == NULL)
		*env_cpy = create_env_var_string(env, name, "");
	else
		*env_cpy = create_env_var_string(env, name, value);
	if (!*env_cpy)
		return (1);
	return (0);
}

int	extract_name_value(char *arg, char **name, char **value, t_env *env)
{
	int	j;

	j = 0;
	if (arg[0] == '=')
		return (printf("Syntax error\n"), 1);
	while (arg[j] && arg[j] != '=')
		j++;
	*name = ft_strndup(arg, j);
	if (!*name)
		return (1);
	if (is_valid_name(*name, j))
        	return (free(*name), 1);
	if (arg[j] == '\0')
	{
		*value = NULL;
		env->equal = 1;
	}
	else
	{
		*value = ft_strdup(arg + j + 1);
		env->equal = 0;
	}
	return (0);
}
