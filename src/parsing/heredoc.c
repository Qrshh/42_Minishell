/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:54:03 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/20 18:24:47 by abesneux         ###   ########.fr       */
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

char	*heredoc_tmp_file(void)
{
	char	*tmpfile;

	tmpfile = malloc(ft_strlen(".heredoc.tmp") + 1);
	if (!tmpfile)
		return (NULL);
	strcpy(tmpfile, ".heredoc.tmp");
	return (tmpfile);
}

int	redir_heredoc(t_word *list)
{
	int	fd;

	fd = open(list->str, O_RDONLY);
	if (fd < 0)
	{
		printf("heredoc open");
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		printf("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	unlink(list->str);
	return (0);
}

void	heredoc_loop(int fd, char *line, char *delimiter)
{
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (!line || g_exit_status == 130)
		{
			printf("EOF incorrect, leaving\n");
			break ;
		}
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
}

int	handle_heredoc(t_word *current)
{
	int		fd;
	char	*delimiter;
	char	*tmpfile;

	if (!current->next)
		return (ft_putstr_fd("Heredoc error \n", STDERR_FILENO), 1);
	delimiter = current->next->str;
	tmpfile = heredoc_tmp_file();
	fd = open(tmpfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putstr_fd("heredoc : error tmp\n", STDERR_FILENO), 1);
	sigaction_handle();
	g_exit_status = 0;
	heredoc_loop(fd, NULL, delimiter);
	close(fd);
	restore_sigint();
	if (g_exit_status == 130)
	{
		unlink(tmpfile);
		free(tmpfile);
		return (1);
	}
	free(current->str);
	current->str = tmpfile;
	return (0);
}
