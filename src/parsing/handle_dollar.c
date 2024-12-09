/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 13:39:06 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/14 17:41:22 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, t_arena *arena)
{
	int		i;
	char	*var_name;

	i = 0;
	if (ft_strcmp(str, "?") == 0)
		return (aft_strdup("?", arena));
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	var_name = aft_substr(str, 0, i, arena);
	return (var_name);
}

char	*replace_var(char *input, char *var_name, char *var_value,
			t_arena *arena)
{
	char	*new_input;
	char	*pos;

	new_input = arena_alloc(arena, sizeof(char) * (ft_strlen(var_value) + 1));
	if (!new_input)
		return (NULL);
	pos = ft_strstr(var_name, input);
	if (pos)
		ft_strncpy(new_input, var_value, ft_strlen(var_value) + 1);
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

void	handle_dollar_var(t_word *current, t_env *env, char *var_name,
			t_arena *arena)
{
	char	*var_value;
	char	*dollar_var_name;

	dollar_var_name = aft_strjoin("$", var_name, arena);
	if (ft_strcmp(var_name, "?") == 0)
	{
		current->str = replace_var(current->str, "$?",
				aft_itoa(g_exit_status, arena), arena);
	}
	else
	{
		var_value = find_var_value(env, var_name);
		if (var_value)
			current->str = replace_var(current->str,
					dollar_var_name, var_value, arena);
		else
			current->str = replace_var(current->str,
					dollar_var_name, "", arena);
	}
}

t_word	*handle_dollar(t_cmd *cmd, t_env *env, t_arena *arena)
{
	t_word	*current;
	char	*var_name;

	current = cmd->list;
	while (current)
	{
		if (current->token == V_ENV)
		{
			var_name = get_var_name(current->str, arena);
			handle_dollar_var(current, env, var_name, arena);
		}
		current = current->next;
	}
	return (cmd->list);
}
