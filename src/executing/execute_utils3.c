/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:51:16 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/20 17:48:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exec(t_cmd *cmd, t_env *env, char *path)
{
	pid_t	pid;
	int		status;

	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, env->env_cpy);
		perror("Command not found");
		exit(127);
	}
	else if (pid < 0)
		perror("Fork error");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	prepare_next_pipe(t_cmd *cmd)
{
	while (cmd->list && cmd->list->token != PIPE)
		cmd->list = cmd->list->next;
	if (cmd->list && cmd->list->token == PIPE)
	{
		cmd->post_pipe = list_to_array(cmd->list->next);
		cmd->list = cmd->list->next;
	}
	else
		cmd->post_pipe = NULL;
}

void	handle_child_process(t_cmd *cmd, t_env *env, int pipefd[2], int fd_in)
{
	dup2(fd_in, STDIN_FILENO);
	if (cmd->nb_pipes > 0)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env);
		exit(g_exit_status);
	}
	else
		exec(cmd, env);
}

void	handle_parent_process(int *fd_in, int pipefd[2], pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
	close(pipefd[1]);
	*fd_in = pipefd[0];
}
