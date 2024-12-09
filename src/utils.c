/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: qrshh <qrshh@student.42.fr>                +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/23 21:07:54 by qrshh             #+#    #+#             */
/*   Updated: 2024/05/23 21:12:04 by qrshh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_and_trim_input(t_arena *arena)
{
	char	*input;
	char	*trimmed_input;

	input = readline("> ");
	if (!input)
		return (NULL);
	else if (*input)
		add_history(input);
	trimmed_input = aft_strtrim(input, " \t", arena);
	return (trimmed_input);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	skip_whitespaces(char *input, int *i)
{
	while (is_space(input[*i]))
		(*i)++;
}

int	reset_cmd(t_cmd *cmd)
{
	if (cmd->input)
		cmd->input = NULL;
	if (cmd->list)
		cmd->list = NULL;
	return (1);
}

t_cmd	*init_cmd(t_cmd *cmd, t_arena *arena)
{
	cmd->args = list_to_array(cmd->list, arena);
	cmd->post_pipe = NULL;
	cmd->nb_pipes = 0;
	cmd->previous = 0;
	cmd->old_out = dup(STDOUT_FILENO);
	cmd->old_inf = dup(STDIN_FILENO);
	return (cmd);
}
