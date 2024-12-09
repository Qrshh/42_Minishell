/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2024/10/09 17:12:28 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 17:21:59 by ozdemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list(t_word *list)
{
	int		count;
	t_word	*temp;

	count = 0;
	temp = list;
	while (temp && ft_strcmp(temp->str, "|") != 0)
	{
		count++;
		temp = temp->next;
	}
	return (count);
}

int	count_pipes(t_word *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->token == PIPE)
			count++;
		list = list->next;
	}
	return (count);
}

int	handle_single_pipe(t_cmd *cmd, t_env *env, pid_t *pid,
			t_arena *arena)
{
	static int	fd_in = 0;
	int			pipefd[2];

	prepare_next_pipe(cmd, arena);
	if (pipe(pipefd) < 0)
		return (-1);
	*pid = fork();
	if (*pid < 0)
		return (-1);
	dup2(fd_in, STDIN_FILENO);
	if (*pid == 0)
		handle_child_process(cmd, env, pipefd, arena);
	close(pipefd[1]);
	if (fd_in != 0)
		close(fd_in);
	fd_in = pipefd[0];
	return (0);
}

void	manage_fds(int *fd_in, int pipefd[2])
{
	close(pipefd[1]);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = pipefd[0];
}

void	setup_pipe(int pipefd[2])
{
	if (pipe(pipefd) < 0)
		exit(EXIT_FAILURE);
}
