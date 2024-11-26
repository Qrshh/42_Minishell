/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:38:07 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/26 17:02:02 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	if (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_tab(cmd->args);
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

void	free_all(t_all *all)
{
	if (all)
	{
		if (all->input)
			free(all->input);
		if (all->list)
			free_list(all->list);
		free(all);
	}
}
