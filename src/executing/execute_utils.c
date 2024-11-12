/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:04:49 by abesneux          #+#    #+#             */
/*   Updated: 2024/11/12 20:30:09 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_all_fd(t_cmd *cmd)
{
	dup2(cmd->old_out, STDOUT_FILENO);
	close(cmd->old_out);
	dup2(cmd->old_inf, STDIN_FILENO);
	close(cmd->old_inf);
}

void	pre_execute(t_word *list, t_env *env)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Erreur d'allocation mémoire pour cmd");
		return ;
	}
	init_cmd(cmd, list);
	cmd->nb_pipes = count_pipes(cmd->list);
	if (handle_operator_exec(cmd))
	{
		g_exit_status = 1;
		reset_all_fd(cmd);
		free(cmd);
		return ;
	}
	if (list->token == 0)
		execute_command(cmd, env);
	reset_all_fd(cmd);
	free_cmd(cmd);
}

char	**free_array(char **array, int i)
{
	while (i > 0)
		free(array[--i]);
	free(array);
	return (NULL);
}

char	**list_to_array(t_word *list)
{
	char	**array;
	int		i;

	array = malloc((count_list(list) + 1) * sizeof(char *));
	if (!array)
		return (perror("Erreur d'allocation mémoire"), NULL);
	i = 0;
	while (list && ft_strcmp(list->str, "|") != 0)
	{
		if (!is_token_redir(list))
		{
			array[i] = ft_strdup(list->str);
			if (!array[i++])
			{
				perror("Erreur d'allocation mémoire");
				return (free_array(array, i));
			}
		}
		else
			list = list->next;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
