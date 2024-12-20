/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abesneux <abesneux@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/11/18 14:51:16 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/20 17:48:26 by abesneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd(t_cmd *cmd)
{
	close(cmd->old_out);
	close(cmd->old_inf);
}

void	simple_exec(t_cmd *cmd, t_env *env, char *path, t_arena *arena)
{
	pid_t	pid;
	int		status;

	if (is_a_builtin(cmd->args[0]))
	{
		g_exit_status = execute_builtin(cmd, env, arena);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, env->env_cpy);
		printf("Command not found\n");
		close_fd(cmd);
		free_arena(arena);
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	prepare_next_pipe(t_cmd *cmd, t_arena *arena)
{
	while (cmd->list && cmd->list->token != PIPE)
		cmd->list = cmd->list->next;
	if (cmd->list && cmd->list->token == PIPE)
	{
		cmd->post_pipe = list_to_array(cmd->list->next, arena);
		cmd->list = cmd->list->next;
	}
	else
		cmd->post_pipe = NULL;
	if (cmd->post_pipe)
		cmd->args = cmd->post_pipe;
}

void	handle_child_process(t_cmd *cmd, t_env *env, int pipefd[2],
			t_arena *arena)
{
	static int	i;

	i = cmd->nb_pipes;
	if (i > 0)
		dup2(pipefd[1], STDOUT_FILENO);
	if (cmd->previous)
		dup2(cmd->previous, STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exec(cmd, env, arena);
}

void	wait_children(pid_t *pids, int i)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (j < i)
	{
		waitpid(pids[j], &status, 0);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
		j++;
	}
}
