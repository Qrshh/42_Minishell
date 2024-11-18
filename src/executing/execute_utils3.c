/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozdemir <ozdemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:51:16 by ozdemir           #+#    #+#             */
/*   Updated: 2024/11/18 17:22:58 by ozdemir          ###   ########.fr       */
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
