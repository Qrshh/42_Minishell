/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:38:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/12/03 13:47:44 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->list)
			free_list(cmd->list);
		if (cmd->args)
			free_tab(cmd->args);
		if (cmd->post_pipe)
			free_tab(cmd->post_pipe);
		free(cmd);
	}
}

void	free_env(t_env *env)
{
	if (env)
	{
		free_tab(env->env_cpy);
		free(env);
	}
}

void	free_list(t_word *list)
{
	t_word	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}
