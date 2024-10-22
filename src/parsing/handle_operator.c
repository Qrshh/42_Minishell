/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:28:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/22 16:48:36 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_outfile(t_word *list)
{
	int	fd;

	fd = -1;
	if (list->token == RIGHT)
		fd = open(list->next->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (list->token == DOUBLE_RIGHT)
		fd = open(list->next->str, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("outfile : error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("pipe : error\n", STDERR_FILENO);
		return (1);
	}
	if (fd > 0)
		close(fd);
	return (0);
}

int	handle_infile(t_word *list)
{
	int	fd;

	fd = -1;
	if (list->token == LEFT)
		fd = open(list->next->str, O_RDONLY);
	if (fd < 0)
		return ((ft_putstr_fd("infile : error\n", STDERR_FILENO), 1));
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return ((ft_putstr_fd("pipe : error\n", STDERR_FILENO), 1));
	if (fd >= 0)
		close(fd);
	return (0);
}

int	handle_operator_exec(t_cmd *cmd)
{
	t_word	*current;

	current = cmd->list;
	while (current)
	{
		if (current->token == RIGHT || current->token == DOUBLE_RIGHT)
		{
			if (handle_outfile(current))
				return (1);
		}
		else if (current->token == LEFT)
		{
			if (handle_infile(current))
				return (1);
		}
		else if (current->token == DOUBLE_LEFT)
		{
			if (handle_heredoc(current->next->str))
				return (1);
			if (redir_heredoc())
				return (1);
		}
		else if (current->token == PIPE)
		{
			cmd->post_pipe = list_to_array(current->next);
			cmd->flag_pipe = 1;
		}
		current = current->next;
	}
	return (0);
}
