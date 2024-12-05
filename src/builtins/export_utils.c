/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:38:02 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/20 18:33:31 by abesneux         ###   ########.fr       */
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
			return (ft_putstr_fd(" not a valid identifier", STDERR_FILENO), 1);
		i++;
	}
	return (0);
}

int	update_or_create_var(t_env *env, char **env_cpy, char *name, char *value, t_arena *arena)
{
	free(*env_cpy);
	if (value == NULL)
		*env_cpy = create_env_var_string(env, name, "", arena);
	else
		*env_cpy = create_env_var_string(env, name, value, arena);
	if (!*env_cpy)
		return (1);
	return (0);
}

int	extract_name_value(char *arg, char **name, char **value, t_env *env, t_arena *arena)
{
	int	j;

	j = 0;
	if (arg[0] == '=')
		return (printf("Syntax error\n"), 1);
	while (arg[j] && arg[j] != '=')
		j++;
	*name = aft_strndup(arg, j, arena);
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
		*value = aft_strdup(arg + j + 1, arena);
		env->equal = 0;
	}
	return (0);
}
