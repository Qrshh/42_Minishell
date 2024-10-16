/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:54:03 by ozdemir           #+#    #+#             */
/*   Updated: 2024/10/16 16:31:38 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
}
void	sigaction_handle(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = heredoc_handler;
	sigaction(SIGINT, &sa, NULL);
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
