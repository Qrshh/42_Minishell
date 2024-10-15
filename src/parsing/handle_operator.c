/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 18:28:53 by abesneux          #+#    #+#             */
/*   Updated: 2024/10/15 16:45:48 by ozdemir          ###   ########.fr       */
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

int	redir_heredoc(void)
{
	int	fd;

	fd = open(".heredoc.tmp", O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("heredoc : tmp error\n", STDERR_FILENO);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("heredoc : redirection error\n", STDERR_FILENO);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	sigaction_handle();
	g_exit_status = 0;
	fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("heredoc : erreur creation tmp\n", STDERR_FILENO);
		return (1);
	}
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_exit_status == 130)
			break ;
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	if (g_exit_status == 130)
	{
		unlink(".heredoc.tmp");
		return (1);
	}
	return (0);
}

int	handle_operator_exec(t_word *list)
{
	t_word	*current;

	current = list;
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
		current = current->next;
	}
	return (0);
}
