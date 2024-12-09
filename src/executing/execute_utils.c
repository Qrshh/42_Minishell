/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:49 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/20 16:25:17 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env(char **main_env, t_arena *arena)
{
	int		i;
	int		len;
	char	**str;

	i = -1;
	len = 0;
	while (main_env[len])
		len++;
	str = arena_alloc(arena, sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (++i < len)
	{
		str[i] = arena_alloc(arena, ft_strlen(main_env[i]) + 1);
		if (!str[i])
			return (NULL);
		ft_strcpy(str[i], main_env[i]);
	}
	str[len] = NULL;
	return (str);
}

void	reset_all_fd(t_cmd *cmd)
{
	dup2(cmd->old_out, STDOUT_FILENO);
	close(cmd->old_out);
	dup2(cmd->old_inf, STDIN_FILENO);
	close(cmd->old_inf);
}

void	pre_execute(t_cmd *cmd, t_env *env, char *input, t_arena *arena)
{
	if (!input)
		return ;
	if (isatty(0))
		signal(SIGQUIT, handle_sigquit);
	init_cmd(cmd, arena);
	cmd->nb_pipes = count_pipes(cmd->list);
	if (handle_operator_exec(cmd, arena))
	{
		reset_all_fd(cmd);
		return ;
	}
	if (cmd->list->token == 0)
		execute_command(cmd, env, arena);
	reset_all_fd(cmd);
}

char	**free_array(char **array, int i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (NULL);
}

char	**list_to_array(t_word *list, t_arena *arena)
{
	char	**array;
	int		i;

	array = arena_alloc(arena, (count_list(list) + 1) * sizeof(char *));
	if (!array)
		return (printf("Erreur d'allocation mémoire\n"), NULL);
	i = 0;
	while (list && ft_strcmp(list->str, "|") != 0)
	{
		if (!is_token_redir(list))
		{
			array[i] = aft_strdup(list->str, arena);
			if (!array[i++])
			{
				printf("Erreur d'allocation mémoire\n");
				return (NULL);
			}
		}
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
