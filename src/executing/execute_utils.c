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

char	**copy_env(char **main_env)
{
	int		i;
	int		len;
	char	**str;

	i = -1;
	len = 0;
	while (main_env[len])
		len++;
	str = malloc(sizeof(char *) * (len + 1));
	if (!str)
		return (NULL);
	while (++i < len)
	{
		str[i] = ft_strdup(main_env[i]);
		if (!str[i])
		{
			while (i > 0)
				free(str[--i]);
			free(str);
			return (NULL);
		}
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

void	pre_execute(t_word *list, t_env *env, char *input)
{
	t_cmd	*cmd;

	if (isatty(0))
		signal(SIGQUIT, handle_sigquit);
	free(input);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
	{
		free_cmd(cmd);
		printf("Erreur d'allocation mémoire pour cmd");
		return ;
	}
	init_cmd(cmd, list);
	cmd->nb_pipes = count_pipes(cmd->list);
	if (handle_operator_exec(cmd))
	{
		reset_all_fd(cmd);
		free_cmd(cmd);
		return ;
	}
	if (list->token == 0)
		execute_command(cmd, env);
	reset_all_fd(cmd);
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
		return (printf("Erreur d'allocation mémoire"), NULL);
	i = 0;
	while (list && ft_strcmp(list->str, "|") != 0)
	{
		if (!is_token_redir(list))
		{
			array[i] = ft_strdup(list->str);
			if (!array[i++])
			{
				printf("Erreur d'allocation mémoire");
				return (free_array(array, i));
			}
		}
		else if (is_token_redir(list) && list->next)
			list = list->next;
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}
